#include "behaviortree_cpp/bt_factory.h"

using namespace BT;

// clang-format off
static const char* xml_text = R"(

 <root BTCPP_format="4" >

     <BehaviorTree ID="MainTree">
            <ReceiveNodeEnums input_node_status="IDLE" input_node_type="Control" />
     </BehaviorTree>

 </root>
 )";
// clang-format on

class ReceiveNodeEnums : public BT::SyncActionNode
{
  public:
  ReceiveNodeEnums(const std::string& name, const BT::NodeConfig& config) :
        BT::SyncActionNode(name, config)
  {
    // NodeType another_node_type;
    // getInput("input_node_type", another_node_type); Uncomment to trigger Seg fault.
  }

  BT::NodeStatus tick() override
  {
    NodeStatus node_status;
    NodeType node_type;
    
    getInput("input_node_status", node_status);
    getInput("input_node_type", node_type);

    std::cout << "Inside tick() with getInput:" << std::endl;
    std::cout << node_status << std::endl;
    std::cout << node_type << std::endl << std::endl;

    return BT::NodeStatus::SUCCESS;
  }

  static BT::PortsList providedPorts()
  {
    return {
      BT::InputPort<NodeStatus>("input_node_status"),
      BT::InputPort<NodeType>("input_node_type"),
    };
  }
};


int main()
{

  BehaviorTreeFactory factory;

  factory.registerNodeType<ReceiveNodeEnums>("ReceiveNodeEnums");

  auto tree = factory.createTreeFromText(xml_text);

  tree.tickWhileRunning();
  std::cout << "Without getInput: " << std::endl;
  std::cout << convertFromString<NodeStatus>("IDLE") << std::endl;
  std::cout << convertFromString<NodeType>("Control") << std::endl << std::endl;

  return 0;
}
