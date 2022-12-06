#!/bin/csh
#######################################################################
# this script will be in the directory "cbp2-infrastructure-v3"
# it assumes that a file called "src.tar.gz" is in that same directory
# and will unpack your project files into the "src" directory.
#######################################################################

# make a temporary directory to hold work

mkdir -p tmp
cd tmp

# unpack student's file into new src directory
tar -xvzf ../src.tar.gz

# if it worked...
if ( -e src ) then

	# copy original files from the infrastructure to the new src directory

	foreach i ( Makefile branch.h trace.cc trace.h predictor.h predict.cc )
		cp -v ../src/$i ./src
	end
else

	# student's file somehow failed to unpack into the right directory

	echo "src directory is missing!"
	exit 1
endif

# make the predict binary

cd src
make
cd ..

# if it worked...
if ( -e src/predict ) then
	ln -fs ../traces traces
	../run traces/
else
	echo "failed to make predict program!"
	exit 1
endif
cd ..
rm -rf tmp
