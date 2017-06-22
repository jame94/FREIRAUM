for d in ../../vvvv/*/
do basename=$(basename $d)
echo "timeout 30" > ../../$basename.bat
echo "start \"\" \"%~dp0\\vvvv\\$basename\\vvvv.exe\" /o \"%~dp0\\Software\\Patches\\_root.v4p\"" >> ../../$basename.bat
done
