type optional('a) =
  | Field('a)
  | Missing;

type snowflake = string;

module Permissions = {
  type role = {
    id: snowflake,
    name: string,
    color: int,
    hoist: bool,
    position: int,
    permissions: int,
    managed: bool,
    mentionable: bool,
  };
};

module User = {
  type t = {
    id: snowflake,
    username: string,
    discriminator: string,
    avatar: option(string),
    bot: optional(bool),
    mfaEnabled: optional(bool),
    locale: optional(string),
    verified: optional(bool),
    email: optional(string),
    flags: optional(int),
    premiumType: optional(int),
  };
};

module Presence = {
  type timestamps = {
    start: optional(int),
    end_: optional(int),
  };

  type party = {
    id: optional(string),
    size: optional(array(int)),
  };

  type assets = {
    largeImage: optional(string),
    largeText: optional(string),
    smallImage: optional(string),
    smallText: optional(string),
  };

  type secrets = {
    join: optional(string),
    spectate: optional(string),
    match: optional(string),
  };

  type activity = {
    name: string,
    type_: int,
    url: optional(option(string)),
    timestamps: optional(timestamps),
    applicationId: optional(snowflake),
    details: optional(option(string)),
    state: optional(option(string)),
    party: optional(party),
    assets: optional(assets),
    secrets: optional(secrets),
    instance: optional(bool),
    flags: optional(int),
  };

  type update = {
    user: User.t,
    roles: array(snowflake),
    game: option(activity),
    guildId: snowflake,
    status: string,
    activities: array(activity),
    clientStatus,
  }
  and clientStatus = {
    desktop: optional(string),
    mobile: optional(string),
    web: optional(string),
  };
};

module Channel = {
  type overwrite = {
    id: snowflake,
    type_: string,
    allow: int,
    deny: int,
  };

  type t = {
    id: snowflake,
    type_: int,
    guildId: optional(snowflake),
    position: optional(int),
    permissionOverwrites: optional(array(overwrite)),
    name: optional(string),
    topic: optional(option(string)),
    nsfw: optional(bool),
    lastMessageId: optional(option(snowflake)),
    bitrate: optional(int),
    userLimit: optional(int),
    rateLimitPerUser: optional(int),
    recipients: optional(array(User.t)),
    icon: optional(option(string)),
    ownerId: optional(snowflake),
    applicationId: optional(snowflake),
    parentId: optional(option(snowflake)),
    lastPinTimestamp: optional(Js.Date.t),
  };

  type create = t;
  type update = t;
  type delete = t;
  type pinsUpdate = {
    channelId: snowflake,
    lastPinTimestamp: optional(Js.Date.t),
  };
};

module Emoji = {
  type t = {
    id: option(snowflake),
    name: string,
    roles: optional(array(string)),
    user: optional(User.t),
    requireColons: optional(bool),
    managed: optional(bool),
    animated: optional(bool),
  };
};

module rec Voice: {
  type state = {
    guildId: snowflake,
    channelId: option(snowflake),
    userId: snowflake,
    member: optional(Guild.member),
  };
} = {
  type state = {
    guildId: snowflake,
    channelId: option(snowflake),
    userId: snowflake,
    member: optional(Guild.member),
  };
}
and Guild: {
  type member = {
    user: User.t,
    nick: optional(string),
    roles: array(string),
    joinedAt: Js.Date.t,
    deaf: bool,
    mute: bool,
  };

  type unavailable = {
    id: string,
    unavailable: bool,
  };

  type t = {
    id: snowflake,
    name: string,
    icon: option(string),
    splash: option(string),
    owner: optional(bool),
    ownerId: snowflake,
    permissions: optional(int),
    region: string,
    afkChannelId: option(snowflake),
    afkTimeout: int,
    embedEnabled: optional(bool),
    embedChannelId: optional(snowflake),
    verificationLevel: int,
    defaultMessageNotifications: int,
    explicitContentFilter: int,
    roles: array(Permissions.role),
    emojis: array(Emoji.t),
    features: array(string),
    mfaLevel: int,
    applicationId: option(snowflake),
    widgetEnabled: optional(bool),
    widgetChannelId: optional(snowflake),
    systemChannelId: option(snowflake),
    joinedAt: optional(Js.Date.t),
    large: optional(bool),
    unavailable: optional(bool),
    memberCount: optional(int),
    voiceStates: optional(array(Voice.state)),
    members: optional(array(member)),
    channels: optional(array(Channel.t)),
    presences: optional(array(Presence.update)),
    maxPresences: optional(option(int)),
    maxMembers: optional(int),
    vanityUrlCode: option(string),
    description: option(string),
    banner: option(string),
  };

  type create = t;
} = {
  type member = {
    user: User.t,
    nick: optional(string),
    roles: array(string),
    joinedAt: Js.Date.t,
    deaf: bool,
    mute: bool,
  };

  type unavailable = {
    id: string,
    unavailable: bool,
  };

  type t = {
    id: snowflake,
    name: string,
    icon: option(string),
    splash: option(string),
    owner: optional(bool),
    ownerId: snowflake,
    permissions: optional(int),
    region: string,
    afkChannelId: option(snowflake),
    afkTimeout: int,
    embedEnabled: optional(bool),
    embedChannelId: optional(snowflake),
    verificationLevel: int,
    defaultMessageNotifications: int,
    explicitContentFilter: int,
    roles: array(Permissions.role),
    emojis: array(Emoji.t),
    features: array(string),
    mfaLevel: int,
    applicationId: option(snowflake),
    widgetEnabled: optional(bool),
    widgetChannelId: optional(snowflake),
    systemChannelId: option(snowflake),
    joinedAt: optional(Js.Date.t),
    large: optional(bool),
    unavailable: optional(bool),
    memberCount: optional(int),
    voiceStates: optional(array(Voice.state)),
    members: optional(array(member)),
    channels: optional(array(Channel.t)),
    presences: optional(array(Presence.update)),
    maxPresences: optional(option(int)),
    maxMembers: optional(int),
    vanityUrlCode: option(string),
    description: option(string),
    banner: option(string),
  };

  type create = t;
};

module Message = {
  type attachment = {
    id: snowflake,
    filename: string,
    size: int,
    url: string,
    proxyUrl: string,
    height: option(int),
    width: option(int),
  };

  type embedFooter = {
    text: string,
    iconUrl: optional(string),
    proxyIconUrl: optional(string),
  };

  type embedImage = {
    url: optional(string),
    proxyUrl: optional(string),
    height: optional(int),
    width: optional(int),
  };

  type embedThumbnail = {
    url: optional(string),
    proxyUrl: optional(string),
    height: optional(int),
    width: optional(int),
  };

  type embedVideo = {
    url: optional(string),
    height: optional(int),
    width: optional(int),
  };

  type embedProvider = {
    name: optional(string),
    url: optional(string),
  };

  type embedAuthor = {
    name: optional(string),
    url: optional(string),
    iconUrl: optional(string),
    proxyIconUrl: optional(string),
  };

  type embedField = {
    name: string,
    value: string,
    inline: optional(bool),
  };

  type embed = {
    title: optional(string),
    type_: optional(string),
    description: optional(string),
    url: optional(string),
    timestamp: optional(Js.Date.t),
    color: optional(int),
    footer: optional(embedFooter),
    image: optional(embedImage),
    thumbnail: optional(embedThumbnail),
    video: optional(embedVideo),
    provider: optional(embedProvider),
    author: optional(embedAuthor),
    field: optional(array(embedField)),
  };

  type reaction = {
    count: int,
    me: bool,
    emoji: Emoji.t,
  };

  type activity = {
    type_: int,
    partyId: optional(string),
  };

  type application = {
    id: snowflake,
    coverImage: optional(string),
    description: string,
    icon: option(string),
    name: string,
  };

  type t = {
    id: snowflake,
    channelId: snowflake,
    guildId: optional(snowflake),
    author: User.t,
    member: optional(Guild.member),
    content: string,
    timestamp: Js.Date.t,
    editedTimestamp: option(Js.Date.t),
    tts: bool,
    mentionEveryone: bool,
    mentions: array(User.t),
    mentionRoles: array(snowflake),
    attachments: array(attachment),
    embeds: array(embed),
    reactions: optional(array(reaction)),
    nonce: optional(option(snowflake)),
    pinned: bool,
    webhookId: optional(snowflake),
    type_: int,
    activity: optional(activity),
    application: optional(application),
  };

  type create = t;
  type update = t;
  type delete = {
    id: snowflake,
    channelId: snowflake,
    guildId: snowflake,
  };

  type deleteBulk = {
    ids: array(snowflake),
    channelId: snowflake,
    guildId: snowflake,
  };

  type reactionAdd = {
    userId: snowflake,
    channelId: snowflake,
    messageId: snowflake,
    guildId: optional(snowflake),
    emoji: Emoji.t,
  };

  type reactionRemove = {
    userId: snowflake,
    channelId: snowflake,
    messageId: snowflake,
    guildId: optional(snowflake),
    emoji: Emoji.t,
  };

  type reactionRemoveAll = {
    channelId: snowflake,
    messageId: snowflake,
    guildId: optional(snowflake),
  };
};

exception UnknownMessage(Js.Json.t);

type ready = {
  v: int,
  user: User.t,
  privateChannels: array(unit),
  guilds: array(Guild.unavailable),
  sessionId: string,
  trace: array(string),
  shard: optional(array(int)),
};

type resumed = {trace: array(string)};

type typingStart = {
  channelId: snowflake,
  guildId: optional(snowflake),
  userId: snowflake,
  timestamp: int,
};

type dispatch =
  | Ready(ready)
  | Resumed(resumed)
  | ChannelCreate(Channel.create)
  | ChannelUpdate(Channel.update)
  | ChannelDelete(Channel.delete)
  | ChannelPinsUpdate(Channel.pinsUpdate)
  | GuildCreate(Guild.t)
  | MessageCreate(Message.create)
  | MessageUpdate(Message.update)
  | MessageDelete(Message.delete)
  | MessageDeleteBulk(Message.deleteBulk)
  | MessageReactionAdd(Message.reactionAdd)
  | MessageReactionRemove(Message.reactionRemove)
  | MessageReactionRemoveAll(Message.reactionRemoveAll)
  | TypingStart(typingStart);

type heartbeat = option(int);

type identify = {
  token: string,
  properties: props,
  compress: optional(bool),
  largeThreshold: optional(int),
  shard: optional(array(int)),
  presence: optional(statusUpdate),
}
and props = {
  os: string,
  browser: string,
  device: string,
}
and statusUpdate = {
  since: option(int),
  game: option(Presence.activity),
  status: string,
  afk: bool,
};

type voiceStateUpdate = {
  guildId: snowflake,
  channelId: option(snowflake),
  selfMute: bool,
  selfDeaf: bool,
};

type resume = {
  token: string,
  sessionId: string,
  seq: int,
};

type requestGuildMembers = {
  guildId: snowflake,
  query: string,
  limit: int,
};

type requestGuildMembersBulk = {
  guildId: array(snowflake),
  query: string,
  limit: int,
};

type invalidSession = bool;

type hello = {
  heartbeatInterval: int,
  trace: array(string),
};

type payload =
  | Dispatch(dispatch)
  | Heartbeat(heartbeat)
  | Identify(identify)
  | StatusUpdate(statusUpdate)
  | VoiceStateUpdate(voiceStateUpdate)
  | Resume(resume)
  | Reconnect
  | RequestGuildMembers(requestGuildMembers)
  | RequestGuildMembersBulk(requestGuildMembersBulk)
  | InvalidSession(invalidSession)
  | Hello(hello)
  | Ack;

type data = {
  op: int,
  d: payload,
  s: optional(int),
  t: optional(string),
};

let op_of_payload = payload =>
  switch (payload) {
  | Dispatch(_) => 0
  | Heartbeat(_) => 1
  | Identify(_) => 2
  | StatusUpdate(_) => 3
  | VoiceStateUpdate(_) => 4
  | Resume(_) => 6
  | Reconnect => 7
  | RequestGuildMembers(_) => 8
  | RequestGuildMembersBulk(_) => 8
  | InvalidSession(_) => 9
  | Hello(_) => 10
  | Ack => 11
  };

let t_of_payload = payload =>
  switch (payload) {
  | Dispatch(dispatch) =>
    Field(
      switch (dispatch) {
      | Ready(_) => "READY"
      | Resumed(_) => "RESUMED"
      | ChannelCreate(_) => "CHANNEL_CREATE"
      | ChannelUpdate(_) => "CHANNEL_UPDATE"
      | ChannelDelete(_) => "CHANNEL_DELETE"
      | ChannelPinsUpdate(_) => "CHANNEL_PINS_UPDATE"
      | GuildCreate(_) => "GUILD_CREATE"
      | MessageCreate(_) => "MESSAGE_CREATE"
      | MessageUpdate(_) => "MESSAGE_UPDATE"
      | MessageDelete(_) => "MESSAGE_DELETE"
      | MessageDeleteBulk(_) => "MESSAGE_DELETE_BULK"
      | MessageReactionAdd(_) => "MESSAGE_REACTION_ADD"
      | MessageReactionRemove(_) => "MESSAGE_REACTION_REMOVE"
      | MessageReactionRemoveAll(_) => "MESSAGE_REACTION_REMOVE_ALL"
      | TypingStart(_) => "TYPING_START"
      },
    )
  | _ => Missing
  };

module Decode = {
  let optionalField = (key, decoder, json) =>
    switch (json |> Json.Decode.optional(Json.Decode.field(key, decoder))) {
    | Some(x) => Field(x)
    | None => Missing
    };

  module Permissions = {
    open Permissions;

    let role = json =>
      Json.Decode.{
        id: json |> field("id", string),
        name: json |> field("name", string),
        color: json |> field("color", int),
        hoist: json |> field("hoist", bool),
        position: json |> field("position", int),
        permissions: json |> field("permissions", int),
        managed: json |> field("managed", bool),
        mentionable: json |> field("mentionable", bool),
      };
  };

  module User = {
    open User;

    let t = json =>
      Json.Decode.{
        id: json |> field("id", string),
        username: json |> field("username", string),
        discriminator: json |> field("discriminator", string),
        avatar: json |> field("avatar", optional(string)),
        bot: json |> optionalField("bot", bool),
        mfaEnabled: json |> optionalField("mfa_enabled", bool),
        locale: json |> optionalField("locale", string),
        verified: json |> optionalField("verified", bool),
        email: json |> optionalField("email", string),
        flags: json |> optionalField("flags", int),
        premiumType: json |> optionalField("premium_type", int),
      };
  };

  module Presence = {
    open Presence;

    let timestamps = json =>
      Json.Decode.{
        start: json |> optionalField("start", int),
        end_: json |> optionalField("end", int),
      };

    let party = json =>
      Json.Decode.{
        id: json |> optionalField("id", string),
        size: json |> optionalField("size", array(int)),
      };

    let assets = json =>
      Json.Decode.{
        largeImage: json |> optionalField("large_image", string),
        largeText: json |> optionalField("large_text", string),
        smallImage: json |> optionalField("small_image", string),
        smallText: json |> optionalField("small_text", string),
      };

    let secrets = json =>
      Json.Decode.{
        join: json |> optionalField("join", string),
        spectate: json |> optionalField("spectate", string),
        match: json |> optionalField("match", string),
      };

    let activity = json =>
      Json.Decode.{
        name: json |> field("name", string),
        type_: json |> field("type", int),
        url: json |> optionalField("url", optional(string)),
        timestamps: json |> optionalField("timestamps", timestamps),
        applicationId: json |> optionalField("application_id", string),
        details: json |> optionalField("details", optional(string)),
        state: json |> optionalField("state", optional(string)),
        party: json |> optionalField("party", party),
        assets: json |> optionalField("assets", assets),
        secrets: json |> optionalField("secrets", secrets),
        instance: json |> optionalField("instance", bool),
        flags: json |> optionalField("flags", int),
      };

    let clientStatus = json =>
      Json.Decode.{
        desktop: json |> optionalField("desktop", string),
        mobile: json |> optionalField("mobile", string),
        web: json |> optionalField("web", string),
      };

    let update = json =>
      Json.Decode.{
        user: json |> field("user", User.t),
        roles: json |> field("roles", array(string)),
        game: json |> field("game", optional(activity)),
        guildId: json |> field("guild_id", string),
        status: json |> field("status", string),
        activities: json |> field("activities", array(activity)),
        clientStatus: json |> field("client_status", clientStatus),
      };
  };

  module Channel = {
    open Channel;

    let overwrite = json =>
      Json.Decode.{
        id: json |> field("id", string),
        type_: json |> field("type", string),
        allow: json |> field("allow", int),
        deny: json |> field("deny", int),
      };

    let t = json =>
      Json.Decode.{
        id: json |> field("id", string),
        type_: json |> field("type", int),
        guildId: json |> optionalField("guild_id", string),
        position: json |> optionalField("position", int),
        permissionOverwrites:
          json |> optionalField("permission_overwrites", array(overwrite)),
        name: json |> optionalField("name", string),
        topic: json |> optionalField("topic", optional(string)),
        nsfw: json |> optionalField("nsfw", bool),
        lastMessageId:
          json |> optionalField("last_message_id", optional(string)),
        bitrate: json |> optionalField("bitrate", int),
        userLimit: json |> optionalField("user_limit", int),
        rateLimitPerUser: json |> optionalField("rate_limit_per_user", int),
        recipients: json |> optionalField("recipients", array(User.t)),
        icon: json |> optionalField("icon", optional(string)),
        ownerId: json |> optionalField("owner_id", string),
        applicationId: json |> optionalField("application_id", string),
        parentId: json |> optionalField("parent_id", optional(string)),
        lastPinTimestamp: json |> optionalField("last_pin_timestamp", date),
      };

    let create = t;
    let update = t;
    let delete = t;
    let pinsUpdate = json =>
      Json.Decode.{
        channelId: json |> field("channel_id", string),
        lastPinTimestamp: json |> optionalField("last_pin_timestamp", date),
      };
  };

  module Emoji = {
    open Emoji;

    let t = json =>
      Json.Decode.{
        id: json |> field("id", optional(string)),
        name: json |> field("name", string),
        roles: json |> optionalField("roles", array(string)),
        user: json |> optionalField("user", User.t),
        requireColons: json |> optionalField("require_colons", bool),
        managed: json |> optionalField("managed", bool),
        animated: json |> optionalField("animated", bool),
      };
  };

  module rec Voice_: {let state: Js.Json.t => Voice.state;} = {
    open Voice;

    let state = json =>
      Json.Decode.{
        guildId: json |> field("guild_id", string),
        channelId: json |> field("channel_id", optional(string)),
        userId: json |> field("user_id", string),
        member: json |> optionalField("member", Guild_.member),
      };
  }
  and Guild_: {
    let member: Js.Json.t => Guild.member;
    let unavailable: Js.Json.t => Guild.unavailable;
    let t: Js.Json.t => Guild.t;
    let create: Js.Json.t => Guild.create;
  } = {
    open Guild;

    let member = json =>
      Json.Decode.{
        user: json |> field("user", User.t),
        nick: json |> optionalField("nick", string),
        roles: json |> field("roles", array(string)),
        joinedAt: json |> field("joined_at", date),
        deaf: json |> field("deaf", bool),
        mute: json |> field("mute", bool),
      };

    let unavailable = json =>
      Json.Decode.{
        id: json |> field("id", string),
        unavailable: json |> field("unavailable", bool),
      };

    let t = json =>
      Json.Decode.{
        id: json |> field("id", string),
        name: json |> field("name", string),
        icon: json |> field("icon", optional(string)),
        splash: json |> field("splash", optional(string)),
        owner: json |> optionalField("owner", bool),
        ownerId: json |> field("owner_id", string),
        permissions: json |> optionalField("permissions", int),
        region: json |> field("region", string),
        afkChannelId: json |> field("afk_channel_id", optional(string)),
        afkTimeout: json |> field("afk_timeout", int),
        embedEnabled: json |> optionalField("embed_enabled", bool),
        embedChannelId: json |> optionalField("embed_channel_id", string),
        verificationLevel: json |> field("verification_level", int),
        defaultMessageNotifications:
          json |> field("default_message_notifications", int),
        explicitContentFilter: json |> field("explicit_content_filter", int),
        roles: json |> field("roles", array(Permissions.role)),
        emojis: json |> field("emojis", array(Emoji.t)),
        features: json |> field("features", array(string)),
        mfaLevel: json |> field("mfa_level", int),
        applicationId: json |> field("application_id", optional(string)),
        widgetEnabled: json |> optionalField("widget_enabled", bool),
        widgetChannelId: json |> optionalField("widget_channel_id", string),
        systemChannelId:
          json |> field("system_channel_id", optional(string)),
        joinedAt: json |> optionalField("joined_at", date),
        large: json |> optionalField("large", bool),
        unavailable: json |> optionalField("unavailable", bool),
        memberCount: json |> optionalField("member_count", int),
        voiceStates:
          json |> optionalField("voice_states", array(Voice_.state)),
        members: json |> optionalField("members", array(member)),
        channels: json |> optionalField("channels", array(Channel.t)),
        presences:
          json |> optionalField("presences", array(Presence.update)),
        maxPresences: json |> optionalField("max_presences", optional(int)),
        maxMembers: json |> optionalField("max_members", int),
        vanityUrlCode: json |> field("vanity_url_code", optional(string)),
        description: json |> field("description", optional(string)),
        banner: json |> field("banner", optional(string)),
      };

    let create = t;
  };

  module Voice = Voice_;
  module Guild = Guild_;

  module Message = {
    open Message;

    let attachment = json =>
      Json.Decode.{
        id: json |> field("id", string),
        filename: json |> field("filename", string),
        size: json |> field("size", int),
        url: json |> field("url", string),
        proxyUrl: json |> field("proxy_url", string),
        height: json |> field("height", optional(int)),
        width: json |> field("width", optional(int)),
      };

    let embedFooter = json =>
      Json.Decode.{
        text: json |> field("text", string),
        iconUrl: json |> optionalField("icon_url", string),
        proxyIconUrl: json |> optionalField("proxy_icon_url", string),
      };

    let embedImage: Js.Json.t => embedImage =
      json =>
        Json.Decode.{
          url: json |> optionalField("url", string),
          proxyUrl: json |> optionalField("proxy_url", string),
          height: json |> optionalField("height", int),
          width: json |> optionalField("width", int),
        };

    let embedThumbnail: Js.Json.t => embedThumbnail =
      json =>
        Json.Decode.{
          url: json |> optionalField("url", string),
          proxyUrl: json |> optionalField("proxy_url", string),
          height: json |> optionalField("height", int),
          width: json |> optionalField("width", int),
        };

    let embedVideo = json =>
      Json.Decode.{
        url: json |> optionalField("url", string),
        height: json |> optionalField("height", int),
        width: json |> optionalField("width", int),
      };

    let embedProvider = json =>
      Json.Decode.{
        name: json |> optionalField("name", string),
        url: json |> optionalField("url", string),
      };

    let embedAuthor = json =>
      Json.Decode.{
        name: json |> optionalField("name", string),
        url: json |> optionalField("url", string),
        iconUrl: json |> optionalField("icon_url", string),
        proxyIconUrl: json |> optionalField("proxy_icon_url", string),
      };

    let embedField = json =>
      Json.Decode.{
        name: json |> field("name", string),
        value: json |> field("value", string),
        inline: json |> optionalField("inline", bool),
      };

    let embed = json =>
      Json.Decode.{
        title: json |> optionalField("title", string),
        type_: json |> optionalField("type", string),
        description: json |> optionalField("description", string),
        url: json |> optionalField("url", string),
        timestamp: json |> optionalField("timestamp", date),
        color: json |> optionalField("color", int),
        footer: json |> optionalField("footer", embedFooter),
        image: json |> optionalField("image", embedImage),
        thumbnail: json |> optionalField("thumbnail", embedThumbnail),
        video: json |> optionalField("video", embedVideo),
        provider: json |> optionalField("provider", embedProvider),
        author: json |> optionalField("author", embedAuthor),
        field: json |> optionalField("field", array(embedField)),
      };

    let reaction = json =>
      Json.Decode.{
        count: json |> field("count", int),
        me: json |> field("me", bool),
        emoji: json |> field("emoji", Emoji.t),
      };

    let activity = json =>
      Json.Decode.{
        type_: json |> field("type", int),
        partyId: json |> optionalField("party_id", string),
      };

    let application = json =>
      Json.Decode.{
        id: json |> field("id", string),
        coverImage: json |> optionalField("cover_image", string),
        description: json |> field("description", string),
        icon: json |> field("icon", optional(string)),
        name: json |> field("name", string),
      };

    let t = json =>
      Json.Decode.{
        id: json |> field("id", string),
        channelId: json |> field("channel_id", string),
        guildId: json |> optionalField("guild_id", string),
        author: json |> field("author", User.t),
        member: json |> optionalField("member", Guild.member),
        content: json |> field("content", string),
        timestamp: json |> field("timestamp", date),
        editedTimestamp: json |> field("edited_timestamp", optional(date)),
        tts: json |> field("tts", bool),
        mentionEveryone: json |> field("mention_everyone", bool),
        mentions: json |> field("mentions", array(User.t)),
        mentionRoles: json |> field("mention_roles", array(string)),
        attachments: json |> field("attachments", array(attachment)),
        embeds: json |> field("embeds", array(embed)),
        reactions: json |> optionalField("reactions", array(reaction)),
        nonce: json |> optionalField("nonce", optional(string)),
        pinned: json |> field("pinned", bool),
        webhookId: json |> optionalField("webhook_id", string),
        type_: json |> field("type", int),
        activity: json |> optionalField("activity", activity),
        application: json |> optionalField("application", application),
      };

    let create = t;
    let update = t;
    let delete = json =>
      Json.Decode.{
        id: json |> field("id", string),
        channelId: json |> field("channel_id", string),
        guildId: json |> field("guild_id", string),
      };

    let deleteBulk = json =>
      Json.Decode.{
        ids: json |> field("ids", array(string)),
        channelId: json |> field("channel_id", string),
        guildId: json |> field("guild_id", string),
      };

    let reactionAdd: Js.Json.t => reactionAdd =
      json =>
        Json.Decode.{
          userId: json |> field("user_id", string),
          channelId: json |> field("channel_id", string),
          messageId: json |> field("message_id", string),
          guildId: json |> optionalField("guild_id", string),
          emoji: json |> field("emoji", Emoji.t),
        };

    let reactionRemove: Js.Json.t => reactionRemove =
      json =>
        Json.Decode.{
          userId: json |> field("user_id", string),
          channelId: json |> field("channel_id", string),
          messageId: json |> field("message_id", string),
          guildId: json |> optionalField("guild_id", string),
          emoji: json |> field("emoji", Emoji.t),
        };

    let reactionRemoveAll = json =>
      Json.Decode.{
        channelId: json |> field("channel_id", string),
        messageId: json |> field("message_id", string),
        guildId: json |> optionalField("guild_id", string),
      };
  };

  let ready = json =>
    Json.Decode.{
      v: json |> field("v", int),
      user: json |> field("user", User.t),
      privateChannels: json |> field("private_channels", array(_ => ())),
      guilds: json |> field("guilds", array(Guild.unavailable)),
      sessionId: json |> field("session_id", string),
      trace: json |> field("_trace", array(string)),
      shard: json |> optionalField("shard", array(int)),
    };

  let resumed = json =>
    Json.Decode.{trace: json |> field("_trace", array(string))};

  let typingStart = json =>
    Json.Decode.{
      channelId: json |> field("channel_id", string),
      guildId: json |> optionalField("guild_id", string),
      userId: json |> field("user_id", string),
      timestamp: json |> field("timestamp", int),
    };

  let hello = json =>
    Json.Decode.{
      heartbeatInterval: json |> field("heartbeat_interval", int),
      trace: json |> field("_trace", array(string)),
    };

  let data = json =>
    Json.Decode.{
      op: json |> field("op", int),
      d:
        json
        |> field("d", j =>
             switch (json |> field("op", int)) {
             | 0 =>
               Dispatch(
                 switch (json |> field("t", string)) {
                 | "READY" => Ready(ready(j))
                 | "RESUMED" => Resumed(resumed(j))
                 | "CHANNEL_CREATE" => ChannelCreate(Channel.create(j))
                 | "CHANNEL_UPDATE" => ChannelUpdate(Channel.update(j))
                 | "CHANNEL_DELETE" => ChannelDelete(Channel.delete(j))
                 | "CHANNEL_PINS_UPDATE" =>
                   ChannelPinsUpdate(Channel.pinsUpdate(j))
                 | "GUILD_CREATE" => GuildCreate(Guild.create(j))
                 | "MESSAGE_CREATE" => MessageCreate(Message.create(j))
                 | "MESSAGE_UPDATE" => MessageUpdate(Message.update(j))
                 | "MESSAGE_DELETE" => MessageDelete(Message.delete(j))
                 | "MESSAGE_DELETE_BULK" =>
                   MessageDeleteBulk(Message.deleteBulk(j))
                 | "MESSAGE_REACTION_ADD" =>
                   MessageReactionAdd(Message.reactionAdd(j))
                 | "MESSAGE_REACTION_REMOVE" =>
                   MessageReactionRemove(Message.reactionRemove(j))
                 | "MESSAGE_REACTION_REMOVE_ALL" =>
                   MessageReactionRemoveAll(Message.reactionRemoveAll(j))
                 | "TYPING_START" => TypingStart(typingStart(j))
                 | _ => raise(UnknownMessage(json))
                 },
               )
             | 7 => Reconnect
             | 9 => InvalidSession(bool(j))
             | 10 => Hello(hello(j))
             | 11 => Ack
             | _ => raise(UnknownMessage(json))
             }
           ),

      s: json |> optionalField("s", int),
      t: json |> optionalField("t", string),
    };
};

module Encode = {
  let required = (encoder, r) => Field(encoder(r));

  let optional = (encoder, r) =>
    switch (r) {
    | Field(x) => Field(encoder(x))
    | Missing => Missing
    };

  let nullOpt = (encoder, r) =>
    switch (r) {
    | None => Json.Encode.null
    | Some(x) => encoder(x)
    };

  let objectOpt = fields =>
    List.fold_right(
      (b, a) =>
        switch (b) {
        | (str, Field(json)) => [(str, json), ...a]
        | (_, Missing) => a
        },
      fields,
      [],
    )
    |> Json.Encode.object_;

  module Presence = {
    open Presence;

    let timestamps = r =>
      Json.Encode.(
        objectOpt([
          ("start", r.start |> optional(int)),
          ("end", r.end_ |> optional(int)),
        ])
      );

    let party = r =>
      Json.Encode.(
        objectOpt([
          ("id", r.id |> optional(string)),
          ("size", r.size |> optional(array(int))),
        ])
      );

    let assets = r =>
      Json.Encode.(
        objectOpt([
          ("large_image", r.largeImage |> optional(string)),
          ("large_text", r.largeText |> optional(string)),
          ("small_image", r.smallImage |> optional(string)),
          ("small_text", r.smallText |> optional(string)),
        ])
      );

    let secrets = r =>
      Json.Encode.(
        objectOpt([
          ("join", r.join |> optional(string)),
          ("spectate", r.spectate |> optional(string)),
          ("match", r.match |> optional(string)),
        ])
      );

    let activity = r =>
      Json.Encode.(
        objectOpt([
          ("name", r.name |> required(string)),
          ("type", r.type_ |> required(int)),
          ("url", r.url |> optional(nullOpt(string))),
          ("timestamps", r.timestamps |> optional(timestamps)),
          ("application_id", r.applicationId |> optional(string)),
          ("details", r.details |> optional(nullOpt(string))),
          ("state", r.state |> optional(nullOpt(string))),
          ("party", r.party |> optional(party)),
          ("assets", r.assets |> optional(assets)),
          ("secrets", r.secrets |> optional(secrets)),
          ("instance", r.instance |> optional(bool)),
          ("flags", r.flags |> optional(int)),
        ])
      );
  };

  let updateStatus = r =>
    Json.Encode.(
      objectOpt([
        ("since", r.since |> required(nullOpt(int))),
        ("game", r.game |> required(nullOpt(Presence.activity))),
        ("status", r.status |> required(string)),
        ("afk", r.afk |> required(bool)),
      ])
    );

  let heartbeat = nullOpt(Json.Encode.int);

  let props = r =>
    Json.Encode.(
      object_([
        ("$os", r.os |> string),
        ("$browser", r.browser |> string),
        ("$device", r.device |> string),
      ])
    );

  let identify = (r: identify) =>
    Json.Encode.(
      objectOpt([
        ("token", r.token |> required(string)),
        ("properties", r.properties |> required(props)),
        ("compress", r.compress |> optional(bool)),
        ("large_threshold", r.largeThreshold |> optional(int)),
        ("shard", r.shard |> optional(array(int))),
        ("presence", r.presence |> optional(updateStatus)),
      ])
    );

  let statusUpdate = r =>
    Json.Encode.(
      object_([
        ("since", r.since |> nullOpt(int)),
        ("game", r.game |> nullOpt(Presence.activity)),
        ("status", r.status |> string),
        ("afk", r.afk |> bool),
      ])
    );

  let voiceStateUpdate = (r: voiceStateUpdate) =>
    Json.Encode.(
      object_([
        ("guild_id", r.guildId |> string),
        ("channel_id", r.channelId |> nullOpt(string)),
        ("self_mute", r.selfMute |> bool),
        ("self_deaf", r.selfDeaf |> bool),
      ])
    );

  let resume = r =>
    Json.Encode.(
      object_([
        ("token", r.token |> string),
        ("session_id", r.sessionId |> string),
        ("seq", r.seq |> int),
      ])
    );

  let requestGuildMembers = (r: requestGuildMembers) =>
    Json.Encode.(
      object_([
        ("guild_id", r.guildId |> string),
        ("query", r.query |> string),
        ("limit", r.limit |> int),
      ])
    );

  let requestGuildMembersBulk = (r: requestGuildMembersBulk) =>
    Json.Encode.(
      object_([
        ("guild_id", r.guildId |> array(string)),
        ("query", r.query |> string),
        ("limit", r.limit |> int),
      ])
    );

  let data = r =>
    Json.Encode.(
      objectOpt([
        ("op", r.op |> required(int)),
        (
          "d",
          switch (r.d) {
          | Heartbeat(payload) => payload |> required(heartbeat)
          | Identify(payload) => payload |> required(identify)
          | StatusUpdate(payload) => payload |> required(statusUpdate)
          | VoiceStateUpdate(payload) =>
            payload |> required(voiceStateUpdate)
          | Resume(payload) => payload |> required(resume)
          | RequestGuildMembers(payload) =>
            payload |> required(requestGuildMembers)
          | RequestGuildMembersBulk(payload) =>
            payload |> required(requestGuildMembersBulk)
          | _ => Missing
          },
        ),
        ("s", r.s |> optional(int)),
        ("t", r.t |> optional(string)),
      ])
    );

  let dataFromPayload = r =>
    Json.Encode.(
      objectOpt([
        ("op", op_of_payload(r) |> required(int)),
        (
          "d",
          switch (r) {
          | Heartbeat(payload) => payload |> required(heartbeat)
          | Identify(payload) => payload |> required(identify)
          | StatusUpdate(payload) => payload |> required(statusUpdate)
          | VoiceStateUpdate(payload) =>
            payload |> required(voiceStateUpdate)
          | Resume(payload) => payload |> required(resume)
          | RequestGuildMembers(payload) =>
            payload |> required(requestGuildMembers)
          | RequestGuildMembersBulk(payload) =>
            payload |> required(requestGuildMembersBulk)
          | _ => Missing
          },
        ),
        ("t", t_of_payload(r) |> optional(string)),
      ])
    );
};