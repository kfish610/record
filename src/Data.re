module Presence = Data_presence;

exception NotImplemented;

type updateStatus = {
  since: option(int),
  game: option(Presence.activity),
  status: string,
  afk: bool,
};

type heartbeat = option(int);

type identify = {
  token: string,
  properties: props,
  compress: option(bool),
  large_threshold: option(int),
  shard: option(array(int)),
  presence: option(updateStatus),
}
and props = {
  os: string,
  browser: string,
  device: string,
};

type hello = {
  heartbeat_interval: int,
  trace: array(string),
};

type payload =
  | Heartbeat(heartbeat)
  | Identify(identify)
  | Hello(hello)
  | Ack;

type data = {
  op: int,
  d: payload,
  s: option(int),
  t: option(string),
};

let op_of_payload = payload =>
  switch (payload) {
  | Heartbeat(_) => 1
  | Identify(_) => 2
  | Hello(_) => 10
  | Ack => 11
  };

module Decode = {
  let hello = json =>
    Hello(
      Json.Decode.{
        heartbeat_interval: json |> field("heartbeat_interval", int),
        trace: json |> field("_trace", array(string)),
      },
    );

  let data = json =>
    Json.Decode.{
      op: json |> field("op", int),
      d:
        json
        |> field(
             "d",
             switch (json |> field("op", int)) {
             | 10 => hello
             | 11 => (_ => Ack)
             | _ => raise(NotImplemented)
             },
           ),

      s: json |> optional(field("s", int)),
      t: json |> optional(field("t", string)),
    };
};

module Encode = {
  let required = (encoder, r) => Some(encoder(r));
  let optional = (encoder, r) =>
    switch (r) {
    | Some(x) => Some(encoder(x))
    | None => None
    };

  let object__ = fields =>
    List.fold_right(
      (b, a) =>
        switch (b) {
        | (str, Some(json)) => [(str, json), ...a]
        | (_, None) => a
        },
      fields,
      [],
    )
    |> Json.Encode.object_;

  module Presence = {
    open Presence;
    let activityTimestamps = r =>
      Json.Encode.(
        object__([
          ("start", r.start |> optional(int)),
          ("end", r.end_ |> optional(int)),
        ])
      );
    let activityParty = r =>
      Json.Encode.(
        object__([
          ("id", r.id |> optional(string)),
          ("size", r.size |> optional(array(int))),
        ])
      );
    let activityAssets = r =>
      Json.Encode.(
        object__([
          ("large_image", r.large_image |> optional(string)),
          ("large_text", r.large_text |> optional(string)),
          ("small_image", r.small_image |> optional(string)),
          ("small_text", r.small_text |> optional(string)),
        ])
      );
    let activitySecrets = r =>
      Json.Encode.(
        object__([
          ("join", r.join |> optional(string)),
          ("spectate", r.spectate |> optional(string)),
          ("match", r.match |> optional(string)),
        ])
      );
    let activity = r =>
      Json.Encode.(
        object__([
          ("name", r.name |> required(string)),
          ("type", r.type_ |> required(int)),
          ("url", r.url |> optional(string)),
          ("timestamps", r.timestamps |> optional(activityTimestamps)),
          ("application_id", r.application_id |> optional(string)),
          ("details", r.details |> optional(string)),
          ("state", r.state |> optional(string)),
          ("party", r.party |> optional(activityParty)),
          ("assets", r.assets |> optional(activityAssets)),
          ("secrets", r.secrets |> optional(activitySecrets)),
          ("instance", r.instance |> optional(bool)),
          ("flags", r.flags |> optional(int)),
        ])
      );
  };

  let updateStatus = r =>
    Json.Encode.(
      object__([
        ("since", r.since |> optional(int)),
        ("game", r.game |> optional(Presence.activity)),
        ("status", r.status |> required(string)),
        ("afk", r.afk |> required(bool)),
      ])
    );

  let heartbeat = Json.Encode.nullable(Json.Encode.int);

  let props = r =>
    Json.Encode.(
      object_([
        ("$os", r.os |> string),
        ("$browser", r.browser |> string),
        ("$device", r.device |> string),
      ])
    );

  let identify = r =>
    Json.Encode.(
      object__([
        ("token", r.token |> required(string)),
        ("properties", r.properties |> required(props)),
        ("compress", r.compress |> optional(bool)),
        ("large_threshold", r.large_threshold |> optional(int)),
        ("shard", r.shard |> optional(array(int))),
        ("presence", r.presence |> optional(updateStatus)),
      ])
    );

  let hello = r =>
    Json.Encode.(
      object_([
        ("heartbeat_interval", r.heartbeat_interval |> int),
        ("_trace", r.trace |> array(string)),
      ])
    );
  let data = r =>
    Json.Encode.(
      object__([
        ("op", r.op |> required(int)),
        (
          "d",
          
            switch (r.d) {
            | Heartbeat(payload) => payload |> required(heartbeat)
            | Identify(payload) => payload |> required(identify)
            | Hello(payload) => payload |> required(hello)
            | Ack => Some(null)
            }
        ),
        ("s", r.s |> optional(int)),
        ("t", r.t |> optional(string)),
      ])
    );
  let dataFromPayload = r =>
    Json.Encode.(
      object_([
        ("op", op_of_payload(r) |> int),
        (
          "d",
          switch (r) {
          | Heartbeat(payload) => payload |> heartbeat
          | Identify(payload) => payload |> identify
          | Hello(payload) => payload |> hello
          | Ack => null
          },
        ),
      ])
    );
};