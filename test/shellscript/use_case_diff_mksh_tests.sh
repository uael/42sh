C_CYAN="\033[36;1m"
C_GREEN="\033[32;1m"
C_RED="\033[31;1m"
C_CLEAR="\033[0m"

REF_SHELL=bash
RENDU_PATH="`pwd`"
echo $RENDU_PATH
TESTS_ROOT="$RENDU_PATH/test/shellscript"
echo $TESTS_ROOT

exit_status=0
count_success=0
count_failure=0

mkdir -p /tmp/bin
cp $RENDU_PATH/42sh /tmp/bin/
cp -f `which ${REF_SHELL}` /tmp/bin/${REF_SHELL}

if [ "$?" -ne "0" ]; then
	exit 1
fi

print_result ()
{
	if [ $1 -eq 0 ]
	then
		/usr/bin/printf $C_GREEN"$2"$C_CLEAR
		count_success=$((count_success+1))
	else
		/usr/bin/printf $C_RED"$2"$C_CLEAR
		count_failure=$((count_failure+1))
		exit_status=1
	fi
	/usr/bin/printf " "
}

diff_test ()
{
	#   Suite:        simple_command
	#   Case:         ls_basic
	#   Case_path:    simple_command/ls_basic
	#   Input_file:   simple_command/ls_basic/input.sh
	test_suite=$1
	test_case=$2
	test_case_path="$TESTS_ROOT/$test_suite/$test_case"
	input_file=$test_case_path/input.sh

	# Diff only if test is present
	if ! [ -f ${input_file} ];
	then
		return
	fi

	test_case_tmp="$test_case_path/.tmp"
	rm -rf $test_case_tmp 2>&1 >/dev/null
	mkdir -p $test_case_tmp

	# 42sh
	test_case_tmp_ftsh_stdout="$test_case_tmp/actual_stdout"
	test_case_tmp_ftsh_stderr="$test_case_tmp/actual_stderr"
	test_case_tmp_ftsh_exit_status="$test_case_tmp/actual_exit_status"
	# echo "========> $test_case_tmp_ftsh_stdout <++++++"
	# echo "========> $test_case_tmp_ftsh_stderr <++++++"
	# echo "========> $test_case_tmp_ftsh_exit_status <++++++"
	/tmp/bin/42sh < ${input_file} > $test_case_tmp_ftsh_stdout 2> $test_case_tmp_ftsh_stderr
	echo "exit_code: $?" > $test_case_tmp_ftsh_exit_status

	# shell
	test_case_tmp_shell_stdout="$test_case_tmp/expected_stdout"
	test_case_tmp_shell_stderr="$test_case_tmp/expected_stderr"
	test_case_tmp_shell_exit_status="$test_case_tmp/expected_exit_status"
	# echo "========> $test_case_tmp_shell_stdout <++++++"
	# echo "========> $test_case_tmp_shell_stderr <++++++"
	# echo "========> $test_case_tmp_shell_exit_status <++++++"
	PS1='' PS2='' /tmp/bin/${REF_SHELL} -o posix < ${input_file} > $test_case_tmp_shell_stdout 2> $test_case_tmp_shell_stderr
	echo "exit_code: $?" > $test_case_tmp_shell_exit_status

	# Selection de la sortie voulu: stdout
	if [ -f $test_case_path/expected_stdout ]; then
		expected_stdout_file=$test_case_path/expected_stdout
	else
		expected_stdout_file=$test_case_tmp_shell_stdout
	fi

	# Selection de la sortie voulu: stderr
	if [ -f $test_case_path/expected_stderr ]; then
		expected_stderr_file=$test_case_path/expected_stderr
	else
		expected_stderr_file=$test_case_tmp_shell_stderr
	fi

	# Selection de la sortie voulu: exit_status
	if [ -f $test_case_path/expected_exit_status ]; then
		expected_exit_status_file=$test_case_path/expected_exit_status
	else
		expected_exit_status_file=$test_case_tmp_shell_exit_status
	fi

	# Diff stdout
	diff $expected_stdout_file $test_case_tmp_ftsh_stdout 2>&1 >/dev/null
	print_result "$?" stdout

	# Diff stderr
	diff $expected_stderr_file $test_case_tmp_ftsh_stderr 2>&1 >/dev/null
	print_result "$?" stderr

	# Diff exit status
	diff $expected_exit_status_file $test_case_tmp_ftsh_exit_status 2>&1 >/dev/null
	print_result "$?" exit_status

	echo "$test_suite/$test_case/input.sh"
}

launch_suite() {
	TEST_SUITE=$1
	for TEST_CASE in $TEST_SUITE/*; do
		if [ -d "${TEST_CASE}" ] && [[ "${TEST_CASE}" != *_NOLOAD ]]; then
			diff_test `basename $TEST_SUITE` `basename $TEST_CASE`
		fi
	done
}

launch_all_suites() {
	for TEST_SUITE in $TESTS_ROOT/*; do
		if [ -d "${TEST_SUITE}" ] && [[ "${TEST_SUITE}" != *_NOLOAD ]]; then
			launch_suite $TEST_SUITE
		fi
	done
}

/usr/bin/printf "============================ START DIFF TESTS ==========================\n"
if [ $# -eq 0 ]; then
	launch_all_suites
elif [ $# -eq 1 ]; then
	launch_suite $TESTS_ROOT/$1
elif [ $# -eq 2 ]; then
	diff_test $1 $2
fi

if [ $count_failure -gt 0 ]; then
	echo "$C_RED\c"
else
	echo "$C_GREEN\c"
fi
echo "============================ $count_failure failed, $count_success passed ============================"
echo "$C_CLEAR\c"
echo "Thx to yyang42/42sh_posix for the tests suites :)"

exit $exit_status
