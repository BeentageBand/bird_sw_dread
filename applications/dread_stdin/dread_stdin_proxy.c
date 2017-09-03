#define OBJECT_IMPLEMENTATION Dread_Stdin_Proxy

#include "dread_stdin_proxy.h"
#include "ipc.h"

CLASS_DEF(Dread_Stdin_Proxy)

void Dread_Stdin_Proxy_Init(void)
{
   Dread_Stdin_Proxy_Class.on_reading = Dread_Stdin_Proxy_Class_on_reading;
   Dread_Stdin_Proxy_Class.on_connection_established = Dread_Stdin_Proxy_Class_on_connection_established;
   Dread_Stdin_Proxy_Class.on_disconnection = Dread_Stdin_Proxy_Class_on_disconnection;
}

void Dread_Stdin_Proxy_Delete(struct Object * const obj)
{}

void Dread_Stdin_Proxy_on_reading(union Dread_Stdin * const super, void const * const data,
size_t const data_size)
{
   IPC_Mail_Id_T mailist = {DREAD_STDIN_READ_RESP};
   if(IPC_Subscribe(maillist,Num_Elems(mailist)))
   {
      IPC_Send(IPC_STDIN_READ_RQ, NULL, 0);
      Mail_T const * mail = IPC_Retrieve_From_Mailist(mailist, Num_Elems(mailist));
      if(NULL == mail && mail->data_size < data_size)
      {
         memcpy(data, mail->data, mail->data_size);
      }
      IPC_Unsubscribe(mailist, Num_Elems(Mailist));
   }
}

void Dread_Stdin_Proxy_on_connection_established(union Dread_Stdin * const super)
{}

void Dread_Stdin_Proxy_on_disconnection(union Dread_Stdin * const super)
{}
   
