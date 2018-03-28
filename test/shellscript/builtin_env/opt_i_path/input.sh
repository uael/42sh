env ls
env PATH= ls #fail
env PATH='' ls #fail
env PATH=/bin ls
env route
env PATH= route #fail
env PATH='' route #fail
env PATH=/sbin route

env -i ls
env -i PATH= ls #fail
env -i PATH='' ls #fail
env -i PATH=/bin ls
env -i route #fail
env -i PATH= route #fail
env -i PATH='' route #fail
env -i PATH=/sbin route
