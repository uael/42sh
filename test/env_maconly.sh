env -i -PBAR -uFOO FOO=bar 2>&1 | grep -o "FOO=bar"
env -i -PBAR FOO=bar -uFOO 2>&1 | grep -o "FOO=bar"
