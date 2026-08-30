import argparse
import assetmixer.assetmixer

parser = argparse.ArgumentParser()

parser.add_argument("--asset_sources", nargs="+", help="The directories that contains all of the assets to build")
parser.add_argument("--asset_destination", help="The destination directory that your assets should be built to")

parser.add_argument("--passes", nargs="*", help="A list of asset pass scripts to run.")

parser.add_argument("--rebuild", "-r", help="Force-rebuilds all assets", action="store_true")


args = parser.parse_args()

#print(args.passes)

assetmixer.assetmixer.build_assets(args.asset_sources, args.asset_destination, args.passes, args.rebuild)