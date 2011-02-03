
# include "testing.h"


static void aux(void * pointer){
	if(pointer == NULL){
		ECHO(("____aux_before_THROW\n"));
		E4C_THROW(WildException, "Nobody will catch me.");
	}else{
		ECHO(("____aux_no_exception_was_thrown\n"));
	}
}

static int ext(void){

	const		e4c_exception * error;
	e4c_bool	is_ready1;
	e4c_bool	is_ready2;

	is_ready1 = e4c_context_is_ready();

	if(is_ready1){
		ECHO(("__ext_the_context_WAS_ready\n"));
	}else{
		ECHO(("__ext_the_context_WAS_NOT_ready\n"));
	}

	ECHO(("__ext_before_REUSING_CONTEXT\n"));

	{
		e4c_reusing_context(error){

			ECHO(("__ext_before_TRY_block\n"));

			E4C_TRY{

				ECHO(("__ext_before_CALL_FUNCTION_aux\n"));

				aux(NULL);

				ECHO(("__ext_after_CALL_FUNCTION_aux\n"));

			}

			ECHO(("__ext_after_TRY_block\n"));

		}
	}

	ECHO(("__ext_after_REUSING_CONTEXT\n"));

	is_ready2 = e4c_context_is_ready();

	if(is_ready2){
		ECHO(("__ext_the_context_IS_ready\n"));
	}else{
		ECHO(("__ext_the_context_IS_NOT_ready\n"));
	}

	if(is_ready1 != is_ready2) return(112233);

	if(error == NULL){

		ECHO(("__ext_there_was_no_error\n"));

		return(0);

	}else{

		ECHO(("__ext_there_was_an_error_%s\n", error->name));

		return(123);
	}

}

DEFINE_TEST(
	h06,
	"A library (exception-aware client) does not catch an exception",
	"This tests simulates a call to an external function (as in a library function). The client code is <em>exception-aware</em>, but the external function cannot simply rely on that. So the external function opens a <code>e4c_reusing_context</code> and then the existing exception context is <em>reused</em>. The external function does not catch an exception so it is propagated to the caller. The caller does not catch it either, so the uncaught exception terminates the program or thread.",
	NULL,
	( E4C_VERSION_THREADSAFE ? EXIT_WHATEVER : EXIT_FAILURE ),
	"____aux_before_THROW",
	"WildException"
){

	int result;

	ECHO(("before_CONTEXT_BEGIN\n"));

	e4c_context_begin(e4c_true, e4c_print_exception);

	ECHO(("before_CALL_FUNCTION_ext\n"));

	result = ext();

	ECHO(("after_CALL_FUNCTION_ext\n"));

	ECHO(("before_CONTEXT_END\n"));

	e4c_context_end();

	ECHO(("after_CONTEXT_END\n"));

	ECHO(("result_was_%d\n", result));

	return(EXIT_SUCCESS);
}
