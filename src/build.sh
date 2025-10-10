tempDirectory="temp"
gameName="game"
buildDirectory="build"

mkdir $tempDirectory
rm $buildDirectory -r
mkdir $buildDirectory

for file in $(find . -type f \( -name "*.cpp" -o -name "*.hpp" \)); do
	cp $file $tempDirectory
done

for file in "$tempDirectory"/*.cpp; do
	g++ -c "$file" -o "$tempDirectory/$(basename "$file" .cpp).o"
done

g++ "$tempDirectory"/*.o -o "$buildDirectory/$gameName"

rm $tempDirectory -r
