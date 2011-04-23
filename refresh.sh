#!/bin/bash

SVNURL=http://smhasher.googlecode.com/svn/trunk/
ROOT=`cd \`dirname $0\`; pwd`

if [[ -d $ROOT/smhasher ]] ; then
    mv $ROOT/smhasher $ROOT/smhasher_prev_`date +'%Y%m%d%H%M%S'`
fi

svn export $SVNURL $ROOT/smhasher

