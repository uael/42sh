python -c 'print "aa bb cc\n"*10' > /tmp/builtin_read_file

exec 42</tmp/builtin_read_file

read -r <&42; echo "$xx $yy"
read -r yy <&42; echo "$xx $yy"
read -- yy <&42; echo "$xx $yy"
read -- xx <&42; echo "$xx $yy"
read -- yy <&42; echo "$xx $yy"
read -- yy xx <&42; echo "$xx $yy"
