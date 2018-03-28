echo "=========1"
cat << \EOF
content1
EOF
echo "=========2"
cat << 'EOF'
content2
EOF
echo "=========3"
cat << 'E''O'"F"
content3
EOF
echo "=========4"
cat << ??
content4
??
echo "=========4"
cat << ?'?'?
content5
???
