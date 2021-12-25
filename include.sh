#!/usr/bin/env bash
MOD_DYNAMICRATES_ROOT="$( cd "$( dirname "${BASH_SOURCE[0]}" )/" && pwd )"

source $MOD_DYNAMICRATES_ROOT"/conf/conf.sh.dist"

if [ -f $MOD_DYNAMICRATES_ROOT"/conf/conf.sh" ]; then
    source $MOD_DYNAMICRATES_ROOT"/conf/conf.sh"
fi
