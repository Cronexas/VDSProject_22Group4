//
// Created by ludwig on 22.11.16.
//
//Changed by schwarz on 08.02.23

#ifndef VDSPROJECT_REACHABILITY_TESTS_H
#define VDSPROJECT_REACHABILITY_TESTS_H

#include <gtest/gtest.h>
#include "Reachability.h"

using namespace ClassProject;

struct ReachabilityTest : testing::Test {
    std::unique_ptr<ClassProject::ReachabilityInterface> fsm2 = std::make_unique<ClassProject::Reachability>(2);
    std::unique_ptr<ClassProject::ReachabilityInterface> fsm4 = std::make_unique<ClassProject::Reachability>(4);
    std::vector<BDD_ID> stateVars2 = fsm2->getStates();
    std::vector<BDD_ID> stateVars4 = fsm4->getStates();
    std::vector<BDD_ID> transitionFunctions;
};

//Check if the reachability constructor throws an runtime error if input size is 0.
TEST_F(ReachabilityTest, ReachabilityConstructorError)
{
    EXPECT_THROW({ClassProject::Reachability Test_Reachability(0);} , std::runtime_error);
}

//Check if functions SetInitState throws a runtime error if the stateVector is bigger than the size we set before.
//
TEST_F(ReachabilityTest, SetInitState)
{
    std::vector<bool> TestInitState = {false,true};
    EXPECT_THROW( {fsm2->setInitState({true, false, false});}, std::runtime_error);
    EXPECT_THROW( {fsm2->setInitState({false});}, std::runtime_error);
    EXPECT_NO_THROW( {fsm2->setInitState({false,false});});
    EXPECT_NO_THROW( {fsm2->setInitState({false,true});});
}

TEST_F(ReachabilityTest, isReachableFunctionalityTest) {
    fsm2->setInitState({false,false});
    //For the default initial state, all bits are assumed to be set to false.
    EXPECT_TRUE(fsm2->isReachable({false, false}));
    EXPECT_FALSE(fsm2->isReachable({false, true}));
    EXPECT_FALSE(fsm2->isReachable({true, false}));
    EXPECT_FALSE(fsm2->isReachable({true, true}));
    //after calling the constructor, the only reachable state should be the initial state. because The default transition
    // function for each state bit is the identity function
}
TEST_F(ReachabilityTest, isReachableFunctionalityTest2) {
    fsm2->setInitState({false,true});
    EXPECT_FALSE(fsm2->isReachable({true, false}));
    EXPECT_FALSE(fsm2->isReachable({false, false}));
    EXPECT_TRUE(fsm2->isReachable({false, true}));
    EXPECT_FALSE(fsm2->isReachable({true, true}));
    //after calling the constructor, the only reachable state should be the initial state. because The default transition
    // function for each state bit is the identity function
}


TEST_F(ReachabilityTest, getStates) {
    std::vector<BDD_ID> States_Expected = {2, 3};
    EXPECT_EQ(States_Expected, fsm2->getStates());
}


TEST_F(ReachabilityTest, isReachableError) {
    EXPECT_THROW( {fsm2->isReachable({true, false, false});}, std::runtime_error);
    EXPECT_NO_THROW( fsm2->isReachable({true, false}););
}

//originally given
/*
TEST_F(ReachabilityTest, HowTo_Example) { // NOLINT

    BDD_ID s0 = stateVars2.at(0);
    BDD_ID s1 = stateVars2.at(1);

    transitionFunctions.push_back(fsm2->neg(s0)); // s0' = not(s0)
    transitionFunctions.push_back(fsm2->neg(s1)); // s1' = not(s1)
    fsm2->setTransitionFunctions(transitionFunctions);

    fsm2->setInitState({false,false});

    ASSERT_TRUE(fsm2->isReachable({false, false}));
    ASSERT_FALSE(fsm2->isReachable({false, true}));
    ASSERT_FALSE(fsm2->isReachable({true, false}));
    ASSERT_TRUE(fsm2->isReachable({true, true}));
}
*/

TEST_F(ReachabilityTest, FourStatesExample) {
    std::vector<BDD_ID> stateVars4 = fsm4->getStates();
    std::vector<BDD_ID> transitionFunctions;
    BDD_ID s0 = stateVars4.at(0);
    BDD_ID s1 = stateVars4.at(1);
    BDD_ID s2 = stateVars4.at(2);
    BDD_ID s3 = stateVars4.at(3);

    transitionFunctions.push_back(fsm4->neg(s3)); // s0' = not(s0)
    transitionFunctions.push_back(fsm4->neg(s0)); // s1' = not(s1)
    transitionFunctions.push_back(fsm4->neg(s1)); // s2' = not(s1)
    transitionFunctions.push_back(fsm4->neg(s2)); // s3' = not(s1)

    fsm4->setTransitionFunctions(transitionFunctions);

    fsm4->setInitState({false,false,true,false});

    EXPECT_TRUE(fsm4->isReachable({false,false,true,false}));
    EXPECT_TRUE(fsm4->isReachable({true,true,true,false}));
    EXPECT_TRUE(fsm4->isReachable({true, false,false,false}));
    EXPECT_TRUE(fsm4->isReachable({true,false,true,true}));

    EXPECT_FALSE(fsm4->isReachable({false,false,false,false}));
    EXPECT_FALSE(fsm4->isReachable({false,false,false,true}));
    EXPECT_FALSE(fsm4->isReachable({false,false,true,true}));
    EXPECT_FALSE(fsm4->isReachable({false,true,false,false}));
    EXPECT_FALSE(fsm4->isReachable({false,true,false,true}));
    EXPECT_FALSE(fsm4->isReachable({false,true,true,false}));
    EXPECT_FALSE(fsm4->isReachable({false,true,true,true}));
    EXPECT_FALSE(fsm4->isReachable({true,false,false,true}));
    EXPECT_FALSE(fsm4->isReachable({true,false,true,false}));
    EXPECT_FALSE(fsm4->isReachable({true,true,false,false}));
    EXPECT_FALSE(fsm4->isReachable({true,true,false,true}));
    EXPECT_FALSE(fsm4->isReachable({true,true,true,true}));

}

#endif