# the following regexes can be used to generate the harmony and disharmony cards from the card-list.csv:

(\d*),(\d*),(\d*),(\d*),([^,]*),([^,]*).*
{\n    boost::shared_ptr<HarmonyCard> harmonyCard\(new HarmonyCard\(\)\);\n    harmonyCard->name="\5";\n    harmonyCard->priority=\1;\n    harmonyCard->energyCost=\2;\n    harmonyCard->beverageCost=\3;\n    harmonyCard->mealCost=\4;\n    {\n        \6\n    }\n    harmonyDeck.push_back\(harmonyCard\);\n}\n
        (\w*)\[(\w*)=([a-zA-Z0-9:]*)\]
        {\n            boost::shared_ptr<events::\1> event\(new events::\1\(\)\);\n            event->\2=\3;\n            harmonyCard->events.push_back\(boost::static_pointer_cast<core::events::PlayerEvent>\(event\)\);\n        }
;(\w*)\[(\w*)=([a-zA-Z0-9:]*)\];?
\n        {\n            boost::shared_ptr<events::\1> event\(new events::\1\(\)\);\n            event->\2=\3;\n            harmonyCard->events.push_back\(boost::static_pointer_cast<core::events::PlayerEvent>\(event\)\);\n        }


disharmony
(\d*),(\d*),([^,]*),(.*)
for\(int i = 0; i < \2; ++i\)\n{\n    boost::shared_ptr<DisharmonyCard> disharmonyCard\(new DisharmonyCard\(\)\);\n    disharmonyCard->name="\3";\n    {\n        \4\n    }\n    disharmonyDeckTier\1.push_back\(disharmonyCard\);\n}
(\w*)\[([^;]*);?([^\]]*)\];?
{\n            boost::shared_ptr<events::\1> event\(new events::\1\(\)\);\n            event->\2;\n        >>>\3;\n            disharmonyCard->events.push_back\(boost::static_pointer_cast<core::events::Event>\(event\)\);\n        }
>>>([^;]*;)
    event->\1
