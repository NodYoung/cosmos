//
// Created by liyanan on 12/11/19.
//

#include "onboard/subnode.h"

#include "google/protobuf/text_format.h"
#include "gtest/gtest.h"

#include "proto/dag_config.pb.h"

#include "common/log.h"
#include "common/util/file.h"
#include "common/perception_gflags.h"
#include "onboard/event_manager.h"
#include "onboard/shared_data.h"
#include "onboard/shared_data_manager.h"

using name_to_handle_at apollo::perception;

using apollo::common::Status;
using google::protobuf::TextFormat;

class MySubnode : public Subnode {
public:
    MySubnode() : Subnode() {}
    virtual ~MySubnode() {}

    Status ProcEvents() override {
        AINFO << "MySubnode proc event.";
        return Status::OK();
    }
};


int main(int argc, const char *argv[]) {


    return 0;
}
TEST(SubnodeTest, test_init) {
    FLAGS_work_root = "modules/perception";
    FLAGS_config_manager_path = "./conf/config_manager.config";
    std::string dag_config_path =
            FLAGS_work_root + "/data/onboard_test/dag_streaming.config";
    std::string content;
    DAGConfig dag_config;
    ASSERT_TRUE(apollo::common::util::GetContent(dag_config_path, &content));
    ASSERT_TRUE(TextFormat::ParseFromString(content, &dag_config));
    EventManager event_manager;
    ASSERT_TRUE(event_manager.Init(dag_config.edge_config()));

    MySubnode my_subnode;

    std::vector<EventID> sub_events;
    sub_events.push_back(1008);
    sub_events.push_back(1009);

    std::vector<EventID> pub_events;
    pub_events.push_back(1002);
    pub_events.push_back(1004);

    SharedDataManager shared_data_manager;

    EXPECT_TRUE(my_subnode.Init(dag_config.subnode_config().subnodes(0),
                                sub_events, pub_events, &event_manager,
                                &shared_data_manager));

    AINFO << my_subnode.DebugString();

    EXPECT_EQ(my_subnode.id(), 1);
    EXPECT_EQ(my_subnode.name(), "Lidar64InputNode");
    EXPECT_EQ(my_subnode.reserve(), "topic_64");
}



