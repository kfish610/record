module Presence = {
  type activityTimestamps = {
    start: option(int),
    end_: option(int),
  };
  type activityParty = {
    id: option(string),
    size: option(array(int)),
  };
  type activityAssets = {
    large_image: option(string),
    large_text: option(string),
    small_image: option(string),
    small_text: option(string),
  };
  type activitySecrets = {
    join: option(string),
    spectate: option(string),
    match: option(string),
  };
  type activity = {
    name: string,
    type_: int,
    url: option(string),
    timestamps: option(activityTimestamps),
    application_id: option(string),
    details: option(string),
    state: option(string),
    party: option(activityParty),
    assets: option(activityAssets),
    secrets: option(activitySecrets),
    instance: option(bool),
    flags: option(int),
  };
};

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

exception NotImplemented;

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
        object_([
          ("start", r.start |> nullable(int)),
          ("end", r.end_ |> nullable(int)),
        ])
      );
    let activityParty = r =>
      Json.Encode.(
        object_([
          ("id", r.id |> nullable(string)),
          ("size", r.size |> nullable(array(int))),
        ])
      );
    let activityAssets = r =>
      Json.Encode.(
        object_([
          ("large_image", r.large_image |> nullable(string)),
          ("large_text", r.large_text |> nullable(string)),
          ("small_image", r.small_image |> nullable(string)),
          ("small_text", r.small_text |> nullable(string)),
        ])
      );
    let activitySecrets = r =>
      Json.Encode.(
        object_([
          ("join", r.join |> nullable(string)),
          ("spectate", r.spectate |> nullable(string)),
          ("match", r.match |> nullable(string)),
        ])
      );
    let activity = r =>
      Json.Encode.(
        object_([
          ("name", r.name |> string),
          ("type", r.type_ |> int),
          ("url", r.url |> nullable(string)),
          ("timestamps", r.timestamps |> nullable(activityTimestamps)),
          ("application_id", r.application_id |> nullable(string)),
          ("details", r.details |> nullable(string)),
          ("state", r.state |> nullable(string)),
          ("party", r.party |> nullable(activityParty)),
          ("assets", r.assets |> nullable(activityAssets)),
          ("secrets", r.secrets |> nullable(activitySecrets)),
          ("instance", r.instance |> nullable(bool)),
          ("flags", r.flags |> nullable(int)),
        ])
      );
  };

  let updateStatus = r =>
    Json.Encode.(
      object__([
        ("since", r.since |> optional(int)),
        ("game", r.game |> optional(Presence.activity)),
        ("status", Some(r.status |> string)),
        ("afk", Some(r.afk |> bool)),
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
        ("token", Some(r.token |> string)),
        ("properties", Some(r.properties |> props)),
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
      object_([
        ("op", r.op |> int),
        (
          "d",
          switch (r.d) {
          | Heartbeat(payload) => payload |> heartbeat
          | Identify(payload) => payload |> identify
          | Hello(payload) => payload |> hello
          | Ack => null
          },
        ),
        ("s", r.s |> nullable(int)),
        ("t", r.t |> nullable(string)),
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
        ("s", null),
        ("t", null),
      ])
    );
};