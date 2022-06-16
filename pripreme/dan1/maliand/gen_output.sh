PROBLEM='maliand'
for inp in ./test/$PROBLEM.dummy.in.*; do
  tmp="$inp"
  IFS='.' read -a arr <<< "$tmp"
  i=0
  out=""
  for token in "${arr[@]}"; do
    if [ "$i" -eq 3 ]; then
      out+='out'
    else
      out+=$token
    fi
    if [ "$i" -lt 4 ]; then
      out+='.'
    fi
    let i+=1
  done
  ./beker_brute_mask < "$inp" > "$out" 
done
for inp in ./test/$PROBLEM.in.*; do
  tmp="$inp"
  IFS='.' read -a arr <<< "$tmp"
  i=0
  out=""
  for token in "${arr[@]}"; do
    if [ "$i" -eq 2 ]; then
      out+='out'
    else
      out+=$token
    fi
    if [ "$i" -lt 3 ]; then
      out+='.'
    fi
    let i+=1
  done
  ./beker_linearno < "$inp" > "$out" 
done
