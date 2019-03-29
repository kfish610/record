type botSettings = {token: string};
type t;
exception SocketClosed(int, string);
exception SocketError(Dom.errorEvent);
let bot: botSettings => Js.Promise.t(t);