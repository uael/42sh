# check order and content of multiple here docs
cat << EOF1 << EOF2 
hi
EOF1
there
EOF2

# check quoted here-doc is protected
#cat << 'EOF'
#hi\
#there
#stuff
#EOF

# check that quoted here-documents don't have \newline processing done
#cat << 'EOF'
#hi\
#there
#EO\
#F
#EOF
#true

# check that \newline is removed at start of here-doc
cat << EO\
F
hi
EOF

# check that \newline removal works for here-doc delimiter
cat << EOF
hi
EO\
F

# check appending of text to file from here document
rm -f /tmp/bash-zzz
cat > /tmp/bash-zzz << EOF
abc
EOF
cat >> /tmp/bash-zzz << EOF
def ghi
jkl mno
EOF
cat /tmp/bash-zzz
rm -f /tmp/bash-zzz

# here-document in subshell
(cat <<EOF | sort -u) | cat -e
abc
geh
def
abc
EOF
echo end

# subshell
(cat <<EOF)
more text in a subshell
EOF
(cat <<EOF; )
some more text in a different subshell
EOF
echo end

# semi-weird examples posted by Wayne Pollack to austin-group mailing list
cat <<'	END'
hello
END
 END
    END
	END
echo world

cat <<END
hello
END\
END
END
echo end ENDEND

cat <<'    END    '
hello
    END    
echo end hello

cat <<END
hello\
END
END
echo end helloEND

cat <<END
hello
\END
END
echo end 'hello<NL>\END'
