#!/bin/bash

if [[ $# -eq 0 ]]
then
   echo -e "using:\n ./InstallR.sh version"
   echo "version in format 3.0.0"
   echo :-e "example: \n ./InstallR.sh 3.0.0"
   exit
fi
ver=$1
echo -e "version="$ver
link="https://cran.gis-lab.info/src/base/R-3/R-"$ver".tar.gz"
name="R-"$ver
tarName=$name".tar.gz"

lsout=$( ls binaries/$name 2> /dev/null )
if ! [ -z $lsout ]
then
   echo "you have installed R"
   exit
fi

cd InstallStuff/distrib

lsout=$( ls $tarName 2> /dev/null )
if [[ -z $lsout ]]
then
   echo "start downloading"
   wget $link > /dev/null
else
   echo "file exist in distrib folder"
fi

echo "install "$name
a=3
tar -tvzf $tarName > /dev/null && echo "Backup is good!" && a=5
if [[ $a != 5 ]]
 then
    echo "archive is broken, wait for reloadind"
    rm $tarName
    wget $link > /dev/null
fi

echo "extract archive"
tar -xvf $tarName > /dev/null
InstallPath="/gpfs/home/iromanov/InstallStuff/Installed/"$name
cd ../Installed
mkdir $name
cd ../distrib/$name
echo "configure "$name
./configure --prefix=$InstallPath > /dev/null
echo "make"
make > /dev/null
echo "make install"
make install > /dev/null
cd ~
cd binaries
echo "create symbolic link"
ExePath=$InstallPath"/bin/R"
ln -s $ExePath $name

cd ~
path_var="/gpfs/home/iromanov/binaries"
grepout=$(cat ~/.bash_profile | grep $)
if [[ -z $grepout ]]
then
  echo "export PATH=$path_var:$PATH" >>~/.bash_profile
else
  echo "bash_profile already has path variable for R"
fi

echo "installation is complete "
