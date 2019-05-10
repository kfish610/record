[%%debugger.chrome];
open Ws;

type botSettings = {token: string};
type t = {
  settings: botSettings,
  ws: WebSocket.t,
};
exception SocketClosed(int, string);
exception SocketError(Dom.errorEvent);
let bot = settings =>
  Js.Promise.make((~resolve, ~reject) => {
    let ws = WebSocket.make("wss://gateway.discord.gg/?v=6&encoding=json");
    WebSocket.(
      ws
      ->on(
          `open_(
            () => {
              Js.log("Opened");
              resolve(. {settings, ws});
            },
          ),
        )
      ->on(
          `close(
            (code, reason) => {
              Js.log("Closed: " ++ string_of_int(code) ++ " " ++ reason);
              reject(. SocketClosed(code, reason));
            },
          ),
        )
      ->on(
          `error(
            error => {
              Js.log("Error: " ++ ErrorEvent.message(error));
              reject(. SocketError(error));
            },
          ),
        )
      ->on(
          `message(
            message =>
              switch ((message |> Json.parseOrRaise |> Data.Decode.data).d) {
              | Hello(hello) =>
                Js.Global.setInterval(
                  () =>
                    ws
                    ->send(
                        Data.Encode.dataFromPayload(Heartbeat(None))
                        |> Json.stringify,
                      )
                    ->ignore,
                  hello.heartbeatInterval,
                )
                |> ignore;
                ws->send(
                  Data.Encode.dataFromPayload(
                    Identify({
                      token: settings.token,
                      properties: {
                        os: Node.Process.process##platform,
                        browser: "record",
                        device: "record",
                      },
                      compress: Missing,
                      largeThreshold: Missing,
                      shard: Missing,
                      presence: Missing,
                    }),
                  )
                  |> Json.stringify,
                );
              | Ack => ()
              | x =>
                Js.log(message);
                Js.log(x);
              },
          ),
        )
      ->ignore
    );
  });