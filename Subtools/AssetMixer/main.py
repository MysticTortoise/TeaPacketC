import argparse
import assetmixer.assetmixer

parser = argparse.ArgumentParser()

parser.add_argument("--asset_sources", nargs="+", help="The directories that contains all of the assets to build")
parser.add_argument("--asset_destination", help="The destination directory that your assets should be built to")

parser.add_argument("--passes", nargs="*", help="A list of asset pass scripts to run.")

parser.add_argument("--rebuild", "-r", help="Force-rebuilds all assets", action="store_true")

parser.add_argument("--passparams", nargs="*", help="A list of extra arguments to be passed to each pass.")

args = parser.parse_args()

extra_args = dict()

if args.passparams is not None:
    for item in args.passparams:
        if "=" in item:
            key, val = item.split("=", 1)
            extra_args[key] = val


assetmixer.assetmixer.build_assets(args.asset_sources, args.asset_destination,
                                   args.passes, args.rebuild, extra_args)