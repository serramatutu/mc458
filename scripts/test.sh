if [ ! -d $1/test ]; then
    echo "'test' directory not found"; \
    exit 1;
fi;

for in_file in $1/test/*.in; do
    echo "Testing $in_file";
    out_file=$(echo "$in_file" | sed -re 's/\.in$$/.out/' );
    answer_file=$(echo "$in_file" | sed -re 's/\.in$$/.ans/' );
    ./bin/$1/$1 < "$in_file" > "$out_file";
    if diff "$answer_file" "$out_file";  then
        echo ">>> Test passed!";
    else
        echo ">>> Test failed!";
        exit 1;
    fi;
    echo;
done