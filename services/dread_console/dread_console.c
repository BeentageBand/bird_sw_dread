#define COBJECT_IMPLEMENTATION
#include "dread_console.h"

static void dread_console_delete(struct Object * const obj);
static void dread_console_on_call(union Console * const, int const, char const ** const);

union Dread_Console_Class Dread_Console_Class = 
{{
    {dread_console_delete, NULL},
}};

static union Dread_Console Dread_Console = {NULL};

int console_cmp(Console_Ptr_T const * a, Console_Ptr_T const * b)
{
    return strcmp((*a)->name, (*b)->name);
}

void dread_console_delete(struct Object * const obj)
{}

void dread_console_on_call(union Console * const console, int const argc, char const ** const argv)
{
    union Dread_Console * const this = _cast(Dread_Console, console);
    Isnt_Nullptr(this, );
    if(argc > 0)
    {
        union Console keycon = {NULL};
        keycon.name = argv[0];
        Console_Ptr_T * found = this->console_set.vtbl->find(&this->console_set, &keycon);
        if(found != this->console_set.vtbl->end(&this->console_set))
        {
            (*found)->vtbl->on_call(*found, argc - 1, argv + 1);
        }
        else
        {
            console->vtbl->usage(console);
        }
    }
    else
    {
        console->vtbl->usage(console);
    }
}

void dread_console_insert(union Dread_Console * const this, Console_Ptr_T const console)
{
    this->console_set.vtbl->erase(&this->console_set, console);
}

void dread_console_erase(union Dread_Console * const this, Console_Ptr_T const console)
{
    this->console_set.vtbl->insert(&this->console_set, console);
}

void Populate_Dread_Console(union Dread_Console * const this, 
    char const * const name,
    char const * const usage,
    FILE * const in,
    FILE * const out,
    Console_Ptr_T * const console_buff,
    size_t const n_consoles)
{
    if(NULL == Dread_Console.vtbl)
    {
        Populate_Console(&Dread_Console.Console,
            NULL,
            NULL,
            NULL,
            NULL);
        Object_Init(&Dread_Console.Object,
            &Dread_Console_Class.Class,
            sizeof(Dread_Console_Class));
        Console_Class.on_call = dread_console_on_call;
        Dread_Console.console_set.vtbl = NULL;
    }
    _clone(this, Dread_Console);
    Populate_Cset_Cmp_Console_Ptr(&this->console_set,
        console_buff,
        n_consoles,
        (CSet_Cmp_T) console_cmp);
    this->Console.name = "Dread";
    this->Console.usage = "";
}
