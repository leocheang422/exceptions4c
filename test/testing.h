
# ifndef TESTING_FRAMEWORK_H

# define TESTING_FRAMEWORK_H

# include <stdio.h>
# include "e4c.h"

# define EXIT_WHATEVER			76543210

# define SEVERITY_CRITICAL		e4c_true
# define SEVERITY_NOT_CRITICAL	e4c_false

# define TYPE_REQUIREMENT		e4c_true
# define TYPE_UNIT_TEST			e4c_false

# define STATUS_PASSED			0
# define STATUS_WARNING			1
# define STATUS_FAILED			2

/*

	WHAT IS "EXIT_WHATEVER" USED FOR?

	1. When an unhandled signal is received, all bets are off

		The behavior of a program when it receives a signal is undefined,
		specially in a multithreaded program.

		There are a few tests in which I check what happens when a signal is
		received and exceptions4c wasn't told to handle it.

		In these tests, the exit code will be implementation-defined, so there's
		no point in checking it.

	2. pthreads-win32/pthread_exit does not meet the specification

		According to PTHREADS specifications:

			"The process shall exit with an exit status of 0 after the last
			thread has been terminated. The behavior shall be as if the
			implementation called exit() with a zero argument at thread
			termination time."

		So, in the event of an uncaught exception, the program SHOULD be
		returning:

			* EXIT_FAILURE		if the library is in single-thread mode.
			* EXIT_SUCCESS		if the library is in multi-thread mode.

		But:

		Since the windows implementation of PTHREADS (at least, pthreads-win32,
		the one I am currently using) returns the value passed as parameter to
		pthread_exit (in this case, PTHREAD_CANCELED) as the actual program exit
		code, I won't check the exit code when the tests are running in
		thread-safe mode.

	That's why I am using EXIT_WHATEVER instead of EXIT_SUCCESS or EXIT_FAILURE
	in some of the unit tests.

*/

# define ERROR_WHATEVER		(void *)87654321

/*

	WHAT IS "ERROR_WHATEVER" USED FOR?

	1. When an unhandled signal is received, all bets are off

		Some platforms make the program dump information regarding the crash.

		For example, when a program compiled by OpenWatcom atempts to dereference
		a null pointer, the following is printed to the error output:

			The instruction at 0x???????? referenced memory at 0x00000000.
			The memory could not be read.
			Exception fielded by 0x????????
			EAX=0x???????? EBX=0x???????? ECX=0x???????? EDX=0x????????
			ESI=0x???????? EDI=0x???????? EBP=0x???????? ESP=0x????????
			EIP=0x???????? EFL=0x???????? CS =0x???????? SS =0x????????
			DS =0x???????? ES =0x???????? FS =0x???????? GS =0x????????
			Stack dump (SS:ESP)
			0x???????? 0x???????? 0x???????? 0x???????? 0x???????? 0x????????
			0x???????? 0x???????? 0x???????? 0x???????? 0x???????? 0x????????
			...

*/


/*
	TESTS
	________________________________________________________________
*/

# define DEFINE_UNIT_TEST(IS_REQUIREMENT, CODE, TITLE, DESCRIPTION, IS_CRITICAL, AT_FAILURE, EXIT_CODE, OUT, ERR) \
	int test_##CODE##_function(); \
	\
	unit_test test_##CODE = { \
		/* is_requirement */		IS_REQUIREMENT, \
		/* code */					#CODE, \
		/* title */					TITLE, \
		/* description */			DESCRIPTION, \
		/* is_critical */			IS_CRITICAL, \
		/* at_failure */			AT_FAILURE, \
		/* function */				test_##CODE##_function, \
		/* expected_exit_code */	EXIT_CODE, \
		/* expected_output */		OUT, \
		/* expected_error */		ERR, \
		/* found_exit_code */		0, \
		/* found_output */			{ 0 }, \
		/* found_error */			{ 0 }, \
		/* unexpected_exit_code */	0, \
		/* unexpected_output */		0, \
		/* unexpected_error */		0, \
		/* status */				0 \
	}; \
	int test_##CODE##_function()

# define DEFINE_TEST(CODE, TITLE, DESCRIPTION, AT_FAILURE, EXIT_CODE, OUT, ERR) \
	DEFINE_UNIT_TEST(TYPE_UNIT_TEST, CODE, TITLE, DESCRIPTION, SEVERITY_CRITICAL, AT_FAILURE, EXIT_CODE, OUT, ERR)

# define DEFINE_REQUIREMENT(CODE, TITLE, DESCRIPTION, IS_CRITICAL, AT_FAILURE, EXIT_CODE, OUT, ERR) \
	DEFINE_UNIT_TEST(TYPE_REQUIREMENT, CODE, TITLE, DESCRIPTION, IS_CRITICAL, AT_FAILURE, EXIT_CODE, OUT, ERR)


E4C_DECLARE_EXCEPTION(WildException);
E4C_DECLARE_EXCEPTION(TamedException);

E4C_DECLARE_EXCEPTION(ChildException);
E4C_DECLARE_EXCEPTION(SiblingException);
E4C_DECLARE_EXCEPTION(ParentException);
E4C_DECLARE_EXCEPTION(GrandparentException);


/*
	SUITES
	________________________________________________________________
*/

# define TEST_DECLARATION(ID) extern unit_test test_##ID;
# define TEST_ENUMERATION(ID) &test_##ID,

# define SUITE(IS_REQUIREMENT, SUITE_CODE, SUITE_TITLE, SUITE_DESCRIPTION) \
	\
	COLLECTION(TEST_DECLARATION) \
	\
	static unit_test * test_array_##SUITE_CODE[] = { \
		COLLECTION(TEST_ENUMERATION) \
	\
	}; \
	\
	static test_collection test_collection_##SUITE_CODE = { \
		/* test */	test_array_##SUITE_CODE, \
		/* count*/	sizeof(test_array_##SUITE_CODE) / sizeof(test_array_##SUITE_CODE[0]) \
	}; \
	\
	test_suite suite_##SUITE_CODE = { \
		/* is_requirement */	IS_REQUIREMENT, \
		/* title */				SUITE_TITLE, \
		/* description*/		SUITE_DESCRIPTION, \
		/* tests */				&test_collection_##SUITE_CODE, \
		/* stats */				{ \
			/* total */				0, \
			/* passed */			0, \
			/* warnings */			0, \
			/* failed */			0 \
								}, \
		/* status */			0 \
	};


# define END_SUITE NEW

# define TEST_SUITE(SUITE_CODE, SUITE_TITLE, SUITE_DESCRIPTION) \
	SUITE(TYPE_UNIT_TEST, SUITE_CODE, SUITE_TITLE, SUITE_DESCRIPTION)

# define REQUIREMENT_SUITE(SUITE_CODE, SUITE_TITLE, SUITE_DESCRIPTION) \
	SUITE(TYPE_REQUIREMENT, SUITE_CODE, SUITE_TITLE, SUITE_DESCRIPTION)

/*
	RUNNERS
	________________________________________________________________
*/

# define SUITE_DECLARATION(ID) extern test_suite suite_##ID;
# define SUITE_ENUMERATION(ID) &suite_##ID,

# define SUITE_COLLECTION(COLLECTION_NAME) \
	\
	COLLECTION(SUITE_DECLARATION) \
	\
	static test_suite * COLLECTION_NAME##_suites[] = { \
		COLLECTION(SUITE_ENUMERATION) \
	}; \
	\
	test_suite_collection COLLECTION_NAME = { \
		/* suite */ COLLECTION_NAME##_suites, \
		/* count */ sizeof(COLLECTION_NAME##_suites) / sizeof(COLLECTION_NAME##_suites[0]) \
	};

# define END_SUITE_COLLECTION NEW


typedef int (*test_function)();

typedef struct unit_test_struct				unit_test;
typedef struct test_suite_struct			test_suite;

typedef struct test_collection_struct		test_collection;
typedef struct test_suite_collection_struct	test_suite_collection;

typedef struct test_runner_struct			test_runner;
typedef struct statistics_struts			statistics;

struct statistics_struts{

	int						total;
	int						passed;
	int						warnings;
	int						failed;
};

struct unit_test_struct{

	e4c_bool				is_requirement;
	const char *			code;
	const char *			title;
	const char *			description;
	e4c_bool				is_critical;
	const char *			at_failure;
	test_function			function;
	int						expected_exit_code;
	const char *			expected_output;
	const char *			expected_error;
	int						found_exit_code;
	char					found_output[640];
	char					found_error[1024 * 2];
	e4c_bool				unexpected_exit_code;
	e4c_bool				unexpected_output;
	e4c_bool				unexpected_error;
	int						status;
};

struct test_suite_struct{

	e4c_bool				is_requirement;
	const char *			title;
	const char *			description;
	test_collection *		tests;
	statistics				stats;
	int						status;
};

struct test_collection_struct{
	unit_test * *			test;
	int						count;
};

struct test_suite_collection_struct{

	test_suite * *			suite;
	int						count;
};

struct test_runner_struct{

	const char *			file_path;
	int						suite_number;
	int						test_number;
	char					buffer[1024];

	const char *			out;
	const char *			err;
	const char *			report;

	test_suite_collection *	suites;

	struct{
		statistics			tests;
		statistics			suites;
		statistics			requirements;
	}						stats;
};

extern int parse_command_line(
	int						argc,
	char *					argv[],
	test_suite_collection *	suite_collection,
	const char *			report,
	const char *			out,
	const char *			err
);

# endif
