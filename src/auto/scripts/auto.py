#!/usr/bin/env python

import rospy
import smach
import smach_ros
from geometry_msgs.msg import Twist
from std_msgs.msg import Int16
from std_msgs.msg import Bool
import time

class INIT0(smach.State):
    def __init__(self):
        smach.State.__init__(self,outcomes=['id','pushBtn0','pushBtn1'])
        self.encResetMg=Int16()
        self.encResetPb=rospy.Publisher('encReset',Int16,queue_size=10)
        self.bt0Mg=False
        self.bt1Mg=False
        self.mMg=Twist()
        self.mPb=rospy.Publisher('cmd_move',Twist,queue_size=10)
    def bt0Cb(self,mg):
        self.bt0Mg|=mg.data
    def bt1Cb(self,mg):
        self.bt1Mg|=mg.data
    def execute(self,userdata):
        self.bt0Mg=False
        self.bt1Mg=False
        self.mPb.publish(self.mMg)
        self.bt0Sb=rospy.Subscriber('bt0',Bool,self.bt0Cb)
        self.bt1Sb=rospy.Subscriber('bt1',Bool,self.bt1Cb)
        for i in {0,1,2}:
            self.encResetMg.data=i
            self.encResetPb.publish(self.encResetMg)
        rospy.sleep(0.5)
        if self.bt0Mg:
            rospy.sleep(1)
            return 'pushBtn0'
        elif self.bt1Mg:
            rospy.sleep(1)
            return 'pushBtn1'
        else:
            return 'id'

class R0(smach.State):
    def __init__(self):
        smach.State.__init__(self,outcomes=['next'])
        self.mMg=Twist()
        ds=rospy.get_param('R0d')
        self.mMg.linear.x=ds[0]
        self.mMg.linear.y=ds[1]
        self.mMg.angular.z=ds[2]
        self.mPb=rospy.Publisher('cmd_move',Twist,queue_size=10)
    def execute(self,userdata):
        self.mPb.publish(self.mMg)
        rospy.sleep(1)
        return 'next'

class STOP0(smach.State):
    def __init__(self):
        smach.State.__init__(self,outcomes=['next'])
    def execute(self,userdata):
        time.sleep(3)
        return 'next'

class RELEASE(smach.State):
    def __init__(self):
        smach.State.__init__(self,outcomes=['next'])
        self.aMg=False
        self.aPb=rospy.Publisher('cmd_arm0',Bool,queue_size=10)
        self.hMg=False
        self.hPb=rospy.Publisher('cmd_hand0',Bool,queue_size=10)
    def execute(self,userdata):
        self.aPb.publish(self.aMg)
        time.sleep(2)

        self.aMg=True
        self.hPb.publish(self.aMg)
        time.sleep(2)

        self.hPb.publish(self.hMg)
        time.sleep(2)
        return 'next'

class L0(smach.State):
    def __init__(self):
        smach.State.__init__(self,outcomes=['next'])
        self.mMg=Twist()
        ds=rospy.get_param('L0d')
        self.mMg.linear.x=ds[0]
        self.mMg.linear.y=ds[1]
        self.mMg.angular.z=ds[2]
        self.mPb=rospy.Publisher('cmd_move',Twist,queue_size=10)
        self.aMg=True
        self.aPb=rospy.Publisher('cmd_arm0',Bool,queue_size=10)
        self.hMg=True
        self.hPb=rospy.Publisher('cmd_hand0',Bool,queue_size=10)
    def execute(self,userdata):
        self.mPb.publish(self.mMg)
        rospy.sleep(2)

        self.hPb.publish(self.hMg)
        time.sleep(2)

        self.aPb.publish(self.aMg)
        time.sleep(2)
        return 'next'
    
class LU0(smach.State):
    def __init__(self):
        smach.State.__init__(self,outcomes=['next'])
        self.mMg=Twist()
        ds=rospy.get_param('LU0d')
        self.mMg.linear.x=ds[0]
        self.mMg.linear.y=ds[1]
        self.mMg.angular.z=ds[2]
        self.mPb=rospy.Publisher('cmd_move',Twist,queue_size=10)
    def execute(self,userdata):
        self.mPb.publish(self.mMg)
        rospy.sleep(2)
        return 'next'

class U0(smach.State):
    def __init__(self):
        smach.State.__init__(self,outcomes=['next'])
        self.mMg=Twist()
        ds=rospy.get_param('U0d')
        self.mMg.linear.x=ds[0]
        self.mMg.linear.y=ds[1]
        self.mMg.angular.z=ds[2]
        self.mPb=rospy.Publisher('cmd_move',Twist,queue_size=10)
    def execute(self,userdata):
        self.mPb.publish(self.mMg)
        rospy.sleep(2)
        return 'next'

class RU0(smach.State):
    def __init__(self):
        smach.State.__init__(self,outcomes=['next'])
        self.mMg=Twist()
        self.mPb=rospy.Publisher('cmd_move',Twist,queue_size=10)
        ds=rospy.get_param('RU0d')
        self.mMg.linear.x=ds[0]
        self.mMg.linear.y=ds[1]
        self.mMg.angular.z=ds[2]
        self.mPb=rospy.Publisher('cmd_move',Twist,queue_size=10)
    def execute(self,userdata):
        self.mPb.publish(self.mMg)
        rospy.sleep(2)
        return 'next'

class U1(smach.State):
    def __init__(self):
        smach.State.__init__(self,outcomes=['next'])
        self.mMg=Twist()
        ds=rospy.get_param('U1d')
        self.mMg.linear.x=ds[0]
        self.mMg.linear.y=ds[1]
        self.mMg.angular.z=ds[2]
        self.mPb=rospy.Publisher('cmd_move',Twist,queue_size=10)
    def execute(self,userdata):
        self.mPb.publish(self.mMg)
        rospy.sleep(2)
        return 'next'

class LU1(smach.State):
    def __init__(self):
        smach.State.__init__(self,outcomes=['next'])
        self.mMg=Twist()
        ds=rospy.get_param('LU1d')
        self.mMg.linear.x=ds[0]
        self.mMg.linear.y=ds[1]
        self.mMg.angular.z=ds[2]
        self.mPb=rospy.Publisher('cmd_move',Twist,queue_size=10)
    def execute(self,userdata):
        self.mPb.publish(self.mMg)
        rospy.sleep(2)
        return 'next'

class U2(smach.State):
    def __init__(self):
        smach.State.__init__(self,outcomes=['next'])
        self.mMg=Twist()
        ds=rospy.get_param('U2d')
        self.mMg.linear.x=ds[0]
        self.mMg.linear.y=ds[1]
        self.mMg.angular.z=ds[2]
        self.mPb=rospy.Publisher('cmd_move',Twist,queue_size=10)
    def execute(self,userdata):
        self.mPb.publish(self.mMg)
        rospy.sleep(2)
        return 'next'

class INIT1(smach.State):
    def __init__(self):
        smach.State.__init__(self,outcomes=['id','pushBtn0','pushBtn1'])
        self.encResetMg=Int16()
        self.encResetPb=rospy.Publisher('encReset',Int16,queue_size=10)
        self.bt0Mg=False
        self.bt1Mg=False
        self.mMg=Twist()
        self.mPb=rospy.Publisher('cmd_move',Twist,queue_size=10)
    def bt0Cb(self,mg):
        self.bt0Mg|=mg.data
    def bt1Cb(self,mg):
        self.bt1Mg|=mg.data
    def execute(self,userdata):
        self.bt0Mg=False
        self.bt1Mg=False
        self.mPb.publish(self.mMg)
        self.bt0Sb=rospy.Subscriber('bt0',Bool,self.bt0Cb)
        self.bt1Sb=rospy.Subscriber('bt1',Bool,self.bt1Cb)
        for i in {0,1,2}:
            self.encResetMg.data=i
            self.encResetPb.publish(self.encResetMg)
        rospy.sleep(0.5)
        if self.bt0Mg:
            rospy.sleep(1)
            return 'pushBtn0'
        elif self.bt1Mg:
            rospy.sleep(1)
            return 'pushBtn1'
        else:
            return 'id'

class R1(smach.State):
    def __init__(self):
        smach.State.__init__(self,outcomes=['next'])
        self.mMg=Twist()
        ds=rospy.get_param('R1d')
        self.mMg.linear.x=ds[0]
        self.mMg.linear.y=ds[1]
        self.mMg.angular.z=ds[2]
        self.mPb=rospy.Publisher('cmd_move',Twist,queue_size=10)
    def execute(self,userdata):
        self.mPb.publish(self.mMg)
        rospy.sleep(2)
        return 'next'

class STOP1(smach.State):
    def __init__(self):
        smach.State.__init__(self,outcomes=['next'])
    def execute(self,userdata):
        time.sleep(2)
        return 'next'

class L1(smach.State):
    def __init__(self):
        smach.State.__init__(self,outcomes=['next'])
        self.mMg=Twist()
        ds=rospy.get_param('L1d')
        self.mMg.linear.x=ds[0]
        self.mMg.linear.y=ds[1]
        self.mMg.angular.z=ds[2]
        self.mPb=rospy.Publisher('cmd_move',Twist,queue_size=10)
    def execute(self,userdata):
        self.mPb.publish(self.mMg)
        rospy.sleep(2)
        return 'next'

class ROTATE(smach.State):
    def __init__(self):
        smach.State.__init__(self,outcomes=['next'])
        self.mMg=Twist()
        ds=rospy.get_param('ROTATEd')
        self.mMg.linear.x=ds[0]
        self.mMg.linear.y=ds[1]
        self.mMg.angular.z=ds[2]
        self.mPb=rospy.Publisher('cmd_move',Twist,queue_size=10)
    def execute(self,userdata):
        self.mPb.publish(self.mMg)
        rospy.sleep(2)
        return 'next'

class U3(smach.State):
    def __init__(self):
        smach.State.__init__(self,outcomes=['next'])
        self.mMg=Twist()
        ds=rospy.get_param('U3d')
        self.mMg.linear.x=ds[0]
        self.mMg.linear.y=ds[1]
        self.mMg.angular.z=ds[2]
        self.mPb=rospy.Publisher('cmd_move',Twist,queue_size=10)
    def execute(self,userdata):
        self.mPb.publish(self.mMg)
        rospy.sleep(2)
        return 'next'

def main():
    rospy.init_node('auto')
    sm=smach.StateMachine(outcomes=[])
    with sm:
        smach.StateMachine.add('INIT0',INIT0(),
                transitions={'id':'INIT0','pushBtn0':'R0','pushBtn1':'INIT1'})
        smach.StateMachine.add('R0',R0(),
                transitions={'next':'STOP0',})
        smach.StateMachine.add('STOP0',STOP0(),
                transitions={'next':'RELEASE'})
        smach.StateMachine.add('RELEASE',RELEASE(),
                transitions={'next':'L0'})
        smach.StateMachine.add('L0',L0(),
                transitions={'next':'LU0'})
        smach.StateMachine.add('LU0',LU0(),
                transitions={'next':'U0'})
        smach.StateMachine.add('U0',U0(),
                transitions={'next':'RU0'})
        smach.StateMachine.add('RU0',RU0(),
                transitions={'next':'U1'})
        smach.StateMachine.add('U1',U1(),
                transitions={'next':'LU1'})
        smach.StateMachine.add('LU1',LU1(),
                transitions={'next':'U2'})
        smach.StateMachine.add('U2',U2(),
                transitions={'next':'INIT1'})
        smach.StateMachine.add('INIT1',INIT1(),
                transitions={'id':'INIT1','pushBtn0':'R0','pushBtn1':'R1'})
        smach.StateMachine.add('R1',R1(),
                transitions={'next':'STOP1'})
        smach.StateMachine.add('STOP1',STOP1(),
                transitions={'next':'L1'})
        smach.StateMachine.add('L1',L1(),
                transitions={'next':'ROTATE'})
        smach.StateMachine.add('ROTATE',ROTATE(),
                transitions={'next':'U3'})
        smach.StateMachine.add('U3',U3(),
                transitions={'next':'INIT0'})

        outcome=sm.execute()
        rospy.spin()

if __name__ == '__main__':
            main()
