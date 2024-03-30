# @ Author: Ondřej Koumar
# @ Email: xkouma02@stud.fit.vutbr.cz
# @ Create Time: 2024-03-30 18:15
# @ Modified time: 2024-03-30 19:57

#!/bin/bash

red="\033[0;31m"
green="\033[0;32m"
no_color="\033[0m"
current_dir="$(dirname $0)"

executable="../build/src/Parser"

counter_successful=0
counter_failed=0

for input_file in "$current_dir"/koubp_files/*.koubp; do
    echo "Processing $input_file"
    base_name=$(basename "$input_file" .koubp)
    rc_file="$current_dir/koubp_files/$base_name.koubp.rc"

    if [ -f "$rc_file" ]; then
        expected_return_code=$(cat "$rc_file")

        $current_dir/$executable "$input_file"
        return_code=$?

        if [ "$return_code" -eq "$expected_return_code" ]; then
            ((counter_successful++))
            echo -e "${green}Test $base_name passed${no_color}"
        else
            ((counter_failed++))
            echo -e "${red}Test $base_name failed${no_color}"
        fi
    else
        echo -e "${red}Error: RC file not found for $base_name${no_color}"
    fi
done

echo "Tests passed: $counter_successful"
echo "Tests failed: $counter_failed"