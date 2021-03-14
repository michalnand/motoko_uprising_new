import functools
import inspect
import pybullet
import time

class PybulletClient():
    """A wrapper for pybullet to manage different clients."""

    def __init__(self, connection_mode=pybullet.DIRECT):
        
        print("creating pybullet client")
        self._client = pybullet.connect(connection_mode)
        self._shapes = {}
        print("connected")

    def __del__(self):
        try:
            pybullet.disconnect(physicsClientId=self._client)
        except pybullet.error:
            print("pybullet.disconnect error")

    def __getattr__(self, name):
        attribute = getattr(pybullet, name)
        if inspect.isbuiltin(attribute):
            attribute = functools.partial(attribute, physicsClientId=self._client)
        '''
        else:
            print("attr ERROR ", name)
        '''
        return attribute
