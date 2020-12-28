
function split() {
    result="$(cut -d$2 -f$3 <<<$1)"
    echo $result
}

function jread() {
    value=''
    if [[ $2 =~ '.' ]]; then
        for i in $(seq 10 $END); do
            v=$(split $2 . $i)
            if [ ! $v ]; then
                break
            fi
            value+="['$v']"
        done
    else
        if [ $2 ]; then
            value="['$2']"
        fi
    fi

    python3 -c "with open('$1', encoding='utf-8') as f: import json; print(json.load(f)$value)" 2>/dev/null
    return 0
}
