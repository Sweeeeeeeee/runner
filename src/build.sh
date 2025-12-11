tempDirectory="temp/"
gameName="game"
buildDirectory="build/"
production=true
flags=""

if [ "$1" == "debug" ]; then
	production=false

	flags+="-g"
fi

mkdir $tempDirectory
rm $buildDirectory -r
mkdir $buildDirectory

for file in $(find . -type f \( -name "*.cpp" -o -name "*.hpp" -o -name "*.ec" \)); do
	cp $file $tempDirectory
done

for file in "$tempDirectory"*.cpp; do
	g++ -c "$file" -o "$tempDirectory$(basename "$file" .cpp).o" $flags
done

g++ "$tempDirectory"*.o -o "$buildDirectory$gameName" $flags

rm $tempDirectory -r
