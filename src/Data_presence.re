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