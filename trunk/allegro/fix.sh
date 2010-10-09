#!/bin/sh
#
# Sets up the Allegro package for building with the specified compiler,
# and if possible converting text files to the desired target format.
#

proc_help()
{
   echo
   echo "Usage: $0 <platform> [--quick|--dtou|--utod|--utom|--mtou]"
   echo
   echo "Where platform is one of: bcc32, beos, djgpp, mingw, msvc, qnx, unix,"
   echo "mac, macosx, macosx-universal, watcom and wii."
   echo "The --quick parameter turns off text file conversion, --dtou converts from"
   echo "DOS/Win32 format to Unix, --utod converts from Unix to DOS/Win32 format,"
   echo "--utom converts from Unix to Macintosh format and --mtou converts from"
   echo "Macintosh to Unix format. If no parameter is specified --quick is assumed."
   echo

   AL_NOCONV="1"
}

proc_fix()
{
   echo "Configuring Allegro for $1 ..."

   if [ "$2" != "none" ]; then
      echo "# generated by fix.sh" > makefile
      echo "MAKEFILE_INC = $2" >> makefile
      echo "include makefile.all" >> makefile
   fi

   echo "/* generated by fix.sh */" > include/allegro/platform/alplatf.h
   echo "#define $3" >> include/allegro/platform/alplatf.h
}

proc_fix_osx_ub()
{
   echo "Configuring Allegro for Mac OSX Universal Binary ..."

   echo "# generated by fix.sh" > makefile
   echo "UB = 1" >> makefile
   echo "MAKEFILE_INC = makefile.osx" >> makefile
   echo "include makefile.all" >> makefile

   echo "/* generated by fix.sh */" > include/allegro/platform/alplatf.h
   echo "#define ALLEGRO_MACOSX" >> include/allegro/platform/alplatf.h
}

proc_fix_wii()
{
   echo "Configuring Allegro for Nintendo Wii (DevkitPro) ..."      
   echo "# generated by fix.sh" > makefile
   echo "include makefile.wii" >> makefile
   
   echo "/* generated by fix.sh */" > include/allegro/platform/alplatf.h
   echo "#define ALLEGRO_WII" >> include/allegro/platform/alplatf.h
}

proc_filelist()
{
   # common files.
   AL_FILELIST=`find . -type f "(" ! -path "*/.*" ")" -a "(" \
      -name "*.c" -o -name "*.cfg" -o -name "*.cpp" -o -name "*.def" -o \
      -name "*.h" -o -name "*.hin" -o -name "*.in" -o -name "*.inc" -o \
      -name "*.m" -o -name "*.m4" -o -name "*.mft" -o -name "*.s" -o \
      -name "*.rc" -o -name "*.rh" -o -name "*.spec" -o -name "*.pl" -o \
      -name "*.txt" -o -name "*._tx" -o -name "makefile*" -o \
      -name "*.inl" -o -name "configure" -o -name "CHANGES" -o \
      -name "AUTHORS" -o -name "THANKS" \
   ")"`

   # touch unix shell scripts?
   if [ "$1" != "omit_sh" ]; then
      AL_FILELIST="$AL_FILELIST `find . -type f -name '*.sh'`"
   fi

   # touch DOS batch files?
   if [ "$1" != "omit_bat" ]; then
      AL_FILELIST="$AL_FILELIST `find . -type f -name '*.bat'`"
   fi
}

proc_utod()
{
   echo "Converting files from Unix to DOS/Win32 ..."
   proc_filelist "omit_sh"
   for file in $AL_FILELIST; do
      if [ "$ALLEGRO_USE_CYGWIN" = "1" ]; then
         unix2dos "$file"
      else
         echo "$file"
         perl -p -e "s/([^\r]|^)\n/\1\r\n/" "$file" > _tmpfile
         touch -r "$file" _tmpfile
         mv _tmpfile "$file"
      fi
   done
}

proc_dtou()
{
   echo "Converting files from DOS/Win32 to Unix ..."
   proc_filelist "omit_bat"
   for file in $AL_FILELIST; do
      if [ "$ALLEGRO_USE_CYGWIN" = "1" ]; then
         dos2unix "$file"
      else
         echo "$file"
         mv "$file" _tmpfile
         tr -d '\015' < _tmpfile > "$file"
         touch -r _tmpfile "$file"
         rm _tmpfile
      fi
   done
   chmod +x *.sh misc/*.sh tools/x11/*.sh misc/*.pl
   if [ -f configure ]; then
      chmod +x configure
   fi
}

proc_utom()
{
   echo "Converting files from Unix to Macintosh ..."
   proc_filelist "omit_sh"
   for file in $AL_FILELIST; do
      echo "$file"
      mv "$file" _tmpfile
      tr '\012' '\015' < _tmpfile > "$file"
      touch -r _tmpfile "$file"
      rm _tmpfile
   done
}

proc_mtou()
{
   echo "Converting files from Macintosh to Unix ..."
   proc_filelist
   for file in $AL_FILELIST; do
      echo "$file"
      mv "$file" _tmpfile
      tr '\015' '\012' < _tmpfile > "$file"
      touch -r _tmpfile "$file"
      rm _tmpfile
   done
}

# prepare allegro for the given platform.

case "$1" in
   "bcc32"   ) proc_fix "Windows (BCC32)"   "makefile.bcc" "ALLEGRO_BCC32";;
   "beos"    ) proc_fix "BeOS"              "makefile.be"  "ALLEGRO_BEOS";;
   "djgpp"   ) proc_fix "DOS (djgpp)"       "makefile.dj"  "ALLEGRO_DJGPP";;
   "mingw"   ) proc_fix "Windows (MinGW)"   "makefile.mgw" "ALLEGRO_MINGW32";;
   "mingw32" ) proc_fix "Windows (MinGW)"   "makefile.mgw" "ALLEGRO_MINGW32";;
   # The 'msvc' target is undocumented in the help message, but is used
   # during the release process by misc/zipup.sh.
   "msvc"    ) proc_fix "Windows (MSVC)"    "makefile.vc"  "ALLEGRO_MSVC";;
   "qnx"     ) proc_fix "QNX"               "makefile.qnx" "ALLEGRO_QNX";;
   "unix"    ) proc_fix "Unix"              "none"         "ALLEGRO_UNIX";;
   "mac"     ) proc_fix "Mac"               "none"         "ALLEGRO_MPW";;
   "macosx"  ) proc_fix "MacOS X"           "makefile.osx" "ALLEGRO_MACOSX";;
   "macosx-universal" ) proc_fix_osx_ub ;;
   "watcom"  ) proc_fix "DOS (Watcom)"      "makefile.wat" "ALLEGRO_WATCOM";;
   "wii"  ) proc_fix_wii ;;
   "help"    ) proc_help;;
   *         ) proc_help;;
esac

# convert all text-file line endings.

if [ "$AL_NOCONV" != "1" ]; then
   case "$2" in
      "--utod"  ) proc_utod "$1";;
      "--dtou"  ) proc_dtou "$1";;
      "--utom"  ) proc_utom "$1";;
      "--mtou"  ) proc_mtou "$1";;
      "--quick" ) echo "No text file conversion performed ...";;
   esac
fi

echo "Done!"
