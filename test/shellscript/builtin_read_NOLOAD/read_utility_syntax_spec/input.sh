python -c 'print "aa bb cc\n"*100' > /tmp/builtin_read_file

exec 42</tmp/builtin_read_file

read -r xx yy zz <&42; echo "$xx $yy"
read -r xx yy <&42; echo "$xx $yy"
read -r xx <&42; echo "$xx $yy"
read -r <&42; echo "$xx $yy"
read xx yy zz <&42; echo "$xx $yy"
read xx yy <&42; echo "$xx $yy"
read xx <&42; echo "$xx $yy"
read <&42; echo "$xx $yy"

read -- xx yy zz <&42; echo "$xx $yy"
read -- xx yy <&42; echo "$xx $yy"
read -- xx <&42; echo "$xx $yy"
read -- <&42; echo "$xx $yy"
