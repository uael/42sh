setenv hello pouet
setenv ahah hehe
env | grep hello | cat -e
env | grep ahah | cat -e
unsetenv hello
env | grep hello | cat -e
env temporary=hello | grep temporary | cat -e
