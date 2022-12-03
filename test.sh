# Compile all solutions once and run them in order

array=($(ls *.cpp))

for file in "${array[@]}" 
do
    echo "$file"
    echo "---------"
    g++ --std c++17 "$file"
    ./a.out
    echo 
done

rm a.out