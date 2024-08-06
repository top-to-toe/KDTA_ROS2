#include "calculator/calculator.hpp"

Calculator::Calculator() : Node("calculator")
{
    auto qos_profile = rclcpp::QoS(rclcpp::KeepLast(10));
    _subscription = create_subscription<ArithmeticArgument>("arithmetic_argument", qos_profile, std::bind(&Calculator::sub_callback, this, _1));
    _service = create_service<ArithmeticOperator>("arithmetic_operator", std::bind(&Calculator::service_callback, this, _1, _2));
    _action_server = rclcpp_action::create_server<ArithmeticChecker>(
        get_node_base_interface(),
        get_node_clock_interface(),
        get_node_logging_interface(),
        get_node_waitables_interface(),
        "arithmetic_checker",
        std::bind(&Calculator::handle_goal, this, _1, _2),
        std::bind(&Calculator::handle_cancel, this, _1),
        std::bind(&Calculator::execute_checker, this, _1));
}

void Calculator::sub_callback(const ArithmeticArgument::SharedPtr msg)
{
    _sub_a = msg->argument_a;
    _sub_b = msg->argument_b;
    _argument_result = _sub_a + _sub_b;
    _operator_str = std::to_string(_sub_a) + operator_str + std::to_string(_sub_b) + "=" + std::to_string(_argument_result);
    RCLCPP_INFO(get_logger(), "Received: {a: %f, b: %f}", _sub_a, _sub_b);
}

void Calculator::service_callback(const std::shared_ptr<ArithmeticOperator::Request> request, std::shared_ptr<ArithmeticOperator::Response> response)
{
    _argument_operator = request->arithmetic_operator;

    if (_argument_operator == request->PLUS)
    {
        _argument_result = _sub_a + _sub_b;
        operator_str = "+";
    }
    else if (_argument_operator == request->MINUS)
    {
        _argument_result = _sub_a - _sub_b;
        operator_str = "-";
    }
    else if (_argument_operator == request->MULTIPLY)
    {
        _argument_result = _sub_a * _sub_b;
        operator_str = "*";
    }
    else if (_argument_operator == request->DIVISION)
    {
        if (_sub_b == 0)
        {
            RCLCPP_ERROR(get_logger(), "Division by zero");
            _argument_result = 0;
            operator_str = "/";
        }
        else
        {
            _argument_result = _sub_a / _sub_b;
            operator_str = "/";
        }
    }
    else
    {
        RCLCPP_ERROR(get_logger(), "Unknown operator");
    }
    _operator_str = std::to_string(_sub_a) + operator_str + std::to_string(_sub_b) + "=" + std::to_string(_argument_result);
    RCLCPP_INFO(get_logger(), "Result: %s", operator_str.c_str());
    response->arithmetic_result = _argument_result;
}

rclcpp_action::GoalResponse Calculator::handle_goal(const rclcpp_action::GoalUUID &uuid, std::shared_ptr<const ArithmeticChecker::Goal> goal_handle)
{
    (void)uuid;
    (void)goal_handle;
    return rclcpp_action::GoalResponse::ACCEPT_AND_EXECUTE;
}

rclcpp_action::CancelResponse Calculator::handle_cancel(const std::shared_ptr<GoalHandleArithmeticChecker> goal_handle)
{
    RCLCPP_INFO(get_logger(), "Recived request to cancel goal");
    (void)goal_handle;
    return rclcpp_action::CancelResponse::ACCEPT;
}

void Calculator::execute_checker(const std::shared_ptr<GoalHandleArithmeticChecker> goal_handle)
{
    RCLCPP_INFO(get_logger(), "Executing goal");
    rclcpp::Rate loop_rate(1);
    float total_sum = 0.0;
    float goal_sum = goal_handle->get_goal()->goal_sum;
    auto feedback = std::make_shared<ArithmeticChecker::Feedback>();

    while ((total_sum < goal_sum) && rclcpp::ok())
    {
        total_sum += _argument_result;
        loop_rate.sleep();
        _partial_formula.push_back(_operator_str);
        feedback->formula = _operator_std.c_str();
        if (_partial_formula.empty())
        {
            RCLCPP_INFO(get_logger(), "please check your formula");
            break;
        }
        RCLCPP_INFO(get_logger(), "Publish feedback");
        for (auto &formula : _partial_formula)
        {
            RCLCPP_INFO(get_logger(), "%s", formula.c_str());
        }
        goal_handle->publish_feedback(feedback);
        loop_rate.sleep();
    }
}