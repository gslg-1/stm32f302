#!/bin/bash
#!!!!!!!!!!!!!!!!!!!!! Don't ferget to set CRLF to LF !!!!!!!!!!!!!!!!!!!!!
echo 'Start shell script '$0

function getRequiredModules()
{
    # get branchname
    cat $1
}

function checkAvailabilityViaCommits()
{
    local IS_PART_OF=0
    local RESULT='FAILURE'
    local COMMIT_HISTORY=$(git log --pretty=format:"%h %s")
    local MOD_OFF_LIST=$(echo $COMMIT_HISTORY | grep Module(off): )
    local MOD_ON_LIST=$(echo $COMMIT_HISTORY | grep Module(on): )
    local LIST_TO_CHECK
    if [ $1 -eq OFF ]
    then
        LIST_TO_CHECK=MOD_OFF_LIST
    else
        LIST_TO_CHECK=MOD_ON_LIST
    fi
    for ELEMENT_M in $LIST_TO_CHECK
    do
        for ELEMENT_N in "${MOD_LIST[@]}"
        do
            if [ $ELEMENT_N -eq $ELEMENT_M  ]
            then 
                IS_PART_OF=1
                break
            fi
        done
        if [$IS_PART_OF -eq 0 ]
        then
            echo "Test of $ELEMENT_N not available"
            exit 1
        else
            IS_PART_OF=0
        fi
    done 
    echo "All Module Tests are available"
    exit 0
}

BRANCH_NAME=$(git branch --show-current)
# Get List of Requirde OffTarget Tests
OFF_TAR_LIST=$(getRequiredModules /docs/dsgn/ci_specs/$BRANCH_NAME.spec)

# Get List of Requirde OnTarget Tests
ON_TAR_LIST=$(getRequiredModules /docs/dsgn/ci_specs/onTargetMTests/$BRANCH_NAME.spec)

# Check for availability of Tests
checkAvailability OFF $OFF_TAR_LIST && checkAvailability ON $ON_TAR_LIST && exit 0 || exit 1
#EOF