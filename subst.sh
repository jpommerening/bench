#!/bin/bash

if test "x$1" = "x" ; then
  echo "Usage: $0 <name>"
  exit 1
fi

sublower=`echo "$1" | tr "A-Z" "a-z"`
subupper=`echo "$1" | tr "a-z" "A-Z"`
subname=`git config --global --get user.name`
subemail=`git config --global --get user.email`
subyear=`date "+%Y"`

origlower="template"
origupper="TEMPLATE"
origname="@NAME@"
origemail="@EMAIL@"
origyear="@YEAR@"

files="LICENSE README.md Makefile *.mk include src test *.xcodeproj .gitignore"

echo "I'll fill in the following information for you:"
echo
echo "Project: $sublower"
echo "Owner:   $subname"
echo "E-Mail:  $subemail"
echo "Year:    $subyear"
echo
read -n 1 -p "Do you want to continue? (y/n) " cont
echo

if ! test "$cont" = "y" ; then
  echo
  echo "You can adjust name & email using git config."
  exit
fi

pushd `dirname $0` >/dev/null

grep -rl "$origname\|$origemail\|$origyear" $files | \
  xargs sed -i.bak "s/$origname/$subname/g;s/$origemail/$subemail/g;s/$origyear/$subyear/g"
grep -rl "$origlower" $files | xargs sed -i.bak "s/$origlower/$sublower/g"
grep -rl "$origupper" $files | xargs sed -i.bak "s/$origupper/$subupper/g"

find . -name "*.bak" -delete

mvfiles=`find $files -name "$origlower*" -or -name "*-$origlower.*"`

for file in $mvfiles; do
  mv "$file" "${file//$origlower/$sublower}"
  git rm -r $file
  git add ${file//$origlower/$sublower}
done

echo
git add $files
git commit -m "Created $sublower project from template."
git remote rename origin template

popd >/dev/null