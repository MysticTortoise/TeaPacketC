#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "GLShaderMixer/glshadermixer.h"

static void print_usage(void)
{
    printf("Usage:\n\n");
    printf("\tgl_shader_mixer_cli input_file output_file [options]\n\n");
    printf("Options:\n\n");

    printf("\t[--type <type>]:\n");
    printf("\t\tSets the shader type. VERT for vertex, FRAG for fragment/pixel.\n");

    printf("\t[--major <version>]:\n");
    printf("\t\tSets the major version target. Supported options: 3, 4\n");

    printf("\t[--minor <version>]:\n");
    printf("\t\tSets the minor version target. Must match with --major to a valid version.\n");

    printf("\t[--platform <platform>]:\n");
    printf("\t\tSets the target GL version. Supported options: GL, ES\n");
}

static const TP_String nullStr = {0, 0};

static TP_String read_file(const char* const path)
{
    FILE* file = fopen(path, "r");
    size_t file_size, bytes_read;
    TP_String text;

    if (file == NULL)
    {
        perror("Could not open file:");
        perror("\n");
        return nullStr;
    }

    fseek(file, 0, SEEK_END);
    file_size = ftell(file);
    rewind(file);

    text.p = malloc(file_size);
    if (text.p == NULL)
    {
        perror("Could not allocate memory to read file!\n");
        printf("Attempted to allocate %ld bytes\n", file_size);
        fclose(file);
        return nullStr;
    }

    bytes_read = fread(text.p, 1, file_size, file);
    text.size = bytes_read;

    fclose(file);
    return text;
}

static tp_bool write_to_file(const char* const path, TP_ByteArray bytes)
{
    FILE* file = fopen(path, "wb");
    if (file == NULL)
    {
        perror("Could not open file to write to!\n");
        return tp_false;
    }

    fwrite(bytes.p, 1, bytes.size, file);
    fclose(file);
    return tp_true;
}

typedef struct
{
    char* input_file;
    char* output_file;

    GLSMix_ShaderType shaderType;
    GLSMix_GLVersion version;
} InputArgs;
static const InputArgs ErrorArgs = {0};

static InputArgs parse_all_args(size_t argc, char** argv)
{
    InputArgs args;
    if (argc < 3)
    {
        return ErrorArgs;
    }

    if (strcmp(argv[1], argv[2]) == 0)
    {
        perror("Do not write input to the same output file!");
        return ErrorArgs;
    }

    args.input_file = argv[1];
    args.output_file = argv[2];

    args.shaderType = GLSMix_ShaderType_Fragment;

    args.version.major = 3;
    args.version.minor = 0;
    args.version.platform = GLSMix_TargetPlatform_GLCORE;
    args.version._ = 0;

    char** argv_stream = &argv[3];
#define VALIDATE_ARGV_STREAM (argv_stream < argv + argc)
#define ASSERT_VALSTREAM assert(VALIDATE_ARGV_STREAM)
    while (VALIDATE_ARGV_STREAM)
    {
        const char* const cur_arg = *argv_stream++;

        if (strcmp(cur_arg, "--type") == 0)
        {
            ASSERT_VALSTREAM;
            const char* const typeStr = *argv_stream++;

            if (strcmp(typeStr, "VERT") == 0)
            {
                args.shaderType = GLSMix_ShaderType_Vertex;
            } else if (strcmp(typeStr, "FRAG") == 0)
            {
                args.shaderType = GLSMix_ShaderType_Fragment;
            } else
            {
                perror("Invalid Argument for --type: Valid arguments are VERT and FRAG");
                return ErrorArgs;
            }
            continue;
        }

        if (strcmp(cur_arg, "--major") == 0)
        {
            ASSERT_VALSTREAM;
            args.version.major = atoi(*argv_stream++);
            continue;
        }

        if (strcmp(cur_arg, "--minor") == 0)
        {
            ASSERT_VALSTREAM;
            args.version.minor = atoi(*argv_stream++);
            continue;
        }

        if (strcmp(cur_arg, "--platform") == 0)
        {
            ASSERT_VALSTREAM;
            const char* const platformStr = *argv_stream++;

            if (strcmp(platformStr, "GL") == 0)
            {
                args.version.platform = GLSMix_TargetPlatform_GLCORE;
            } else if (strcmp(platformStr, "ES") == 0)
            {
                args.version.platform = GLSMix_TargetPlatform_GLES;
            } else
            {
                perror("Invalid Argument for --platform: Valid arguments are GL and ES");
                return ErrorArgs;
            }
            continue;
        }

        if (strcmp(cur_arg, "--help") == 0)
        {
            return ErrorArgs;
        }
    }
    return args;
}

int main(int argc, char** argv)
{
    const InputArgs args = parse_all_args(argc, argv);
    TP_String input_code;

    if (args.input_file == NULL)
    {
        print_usage();
        return -1;
    }


    input_code = read_file(args.input_file);
    if (input_code.p == NULL)
    {
        goto exit_input;
    }

    {
        TP_StringView codeView = TP_StrViewFromStr(input_code);
        GLSMix_TargetContext targetContext;
        GLSMix_SrcContext srcContext;

        targetContext.version = args.version;
        srcContext.shaderType = args.shaderType;

        TP_ByteArray out = GLSMix_MixDownShader(codeView, &targetContext, &srcContext);
        write_to_file(argv[2], out);
    }

    exit_input:
    free(input_code.p);

    return 0;
}