#define COBJECT_IMPLEMENTATION
#define Dbg_FID CONSOLE_FID, 3

#include "arg_parser.h"
#include "application.h"
#include "console_composite.h"
#include "dbg_log.h"
#include "dread_console_cbk.h"
#include "dread_console_set.h"
#include "dread_console_worker.h"
#include "ipc.h"

#define Dread_Console_MID_Subcription(mid, proc) mid,
#define DREAD_CONSOLE_LINE_FMT "%"STR(DREAD_CONSOLE_LENGTH)"[^\n]"

static void dread_console_worker_delete(struct Object * const obj);
static void dread_console_worker_on_start(union Worker * const super);
static void dread_console_worker_on_mail(union Worker * const super, union Mail * const mail);
static void dread_console_worker_on_loop(union Worker * const super);
static void dread_console_worker_on_stop(union Worker * const super);
static char const ** dread_console_split(char * str, char const delim, size_t * const num_elems);

union Dread_Console_Worker_Class Dread_Console_Worker_Class =
{
        {dread_console_worker_delete, NULL}
};

static union Dread_Console_Worker Dread_Console_Worker = {NULL};
static union Mail Dread_Console_Worker_Mailbox[64] = {0};
static union Console_Composite Dread_Console = {NULL};
static Console_Ptr_T Dread_Console_Buff[IPC_MAX_TID] = {0};
static union Arg_Parser Dread_Parser = {NULL};
static char Dread_StdIn_Buff [DREAD_CONSOLE_LENGTH + 1UL] = {0};
static char * Dread_Console_Arg_Buff[DREAD_CONSOLE_ARG_LENGTH] = {0};

void dread_console_worker_delete(struct Object * const obj)
{}

void dread_console_worker_on_start(union Worker * const super)
{
    Application_initialized();
}

void dread_console_worker_on_mail(union Worker * const super, union Mail * const mail)
{
}

void dread_console_worker_on_loop(union Worker * const super)
{
    union Dread_Console_Worker * const this = _cast(Dread_Console_Worker, super);
    Isnt_Nullptr(this, );
    union Console * cli = &this->dread_console->Console;

    Isnt_Nullptr(cli->in, );

    size_t argc = 0;
    char const ** const argv = Dread_Parser.vtbl->parse(&Dread_Parser, &argc, cli->in);
    if(0 == argc) return;
	Dbg_Info("%s: argc %d argv %s", __func__, argc, (NULL != argv)? argv[0] : "NULL");

    if(NULL != argv)
    {
        cli->vtbl->on_call(cli, argc, argv);
        memset(Dread_StdIn_Buff, 0, sizeof(Dread_StdIn_Buff));
    }
}

void dread_console_worker_on_stop(union Worker * const super)
{
    Application_terminated();
}

void Populate_Dread_Console_Worker(union Dread_Console_Worker * const this)
{
    if(NULL == Dread_Console_Worker.vtbl)
    {
        Populate_Worker(&Dread_Console_Worker.Worker,
                DREAD_CONSOLE_WORKER_TID,
                Dread_Console_Worker_Mailbox,
                Num_Elems(Dread_Console_Worker_Mailbox));
        Object_Init(&Dread_Console_Worker.Object,
                &Dread_Console_Worker_Class.Class,
                sizeof(Dread_Console_Worker_Class.Worker));

        Dread_Console_Worker_Class.Worker.on_start = dread_console_worker_on_start;
        Dread_Console_Worker_Class.Worker.on_mail  = dread_console_worker_on_mail;
        Dread_Console_Worker_Class.Worker.on_loop  = dread_console_worker_on_loop;
        Dread_Console_Worker_Class.Worker.on_stop  = dread_console_worker_on_stop;


        Populate_Console_Composite(&Dread_Console,
                "dread",
                NULL,
                stdin,
                stdout,
                Dread_Console_Buff,
                Num_Elems(Dread_Console_Buff));

        Dread_Console_Worker.dread_console = &Dread_Console;

        Populate_Arg_Parser(&Dread_Parser,
        		Dread_StdIn_Buff,
        		Num_Elems(Dread_StdIn_Buff),
				Dread_Console_Arg_Buff,
				Num_Elems(Dread_Console_Arg_Buff));

		Dread_Console_Factory(&Dread_Console);
    }
    _clone(this, Dread_Console_Worker);
}
