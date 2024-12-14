
class ObjectType:
    VAR = 0
    ARR = 1
    REC = 2


class DataType:
    I32 = 0
    I16 = 1
    I8 = 2
    U32 = 3
    U16 = 4
    U8 = 5
    IQ24 = 6
    IQ15 = 7
    IQ7 = 8,
    STR = 9,
    MEM = 10

    _str_to_type = {
        'I32': I32,
        'I16': I16,
        'I8': I8,
        'U32': U32,
        'U16': U16,
        'U8': U8,
        'IQ24': IQ24,
        'IQ15': IQ15,
        'IQ7': IQ7,
        'STR': STR,
        'MEM': MEM
    }

    _type_size = {
        I32: 4,
        I16: 2,
        I8: 1,
        U32: 4,
        U16: 2,
        U8: 1,
        IQ24: 4,
        IQ15: 4,
        IQ7: 4,
        STR: 0,
        MEM: 0
    }

    @staticmethod
    def fromStr(str_type) -> int:
        if str_type not in DataType._str_to_type:
            return 0
        return DataType._str_to_type[str_type]

    @staticmethod
    def getSize(dataType: int) -> int:
        if dataType in DataType._type_size:
            return DataType._type_size[dataType]
        return 0



class RegFlag:
    NONE = 0
    CONF = 1
    READONLY = 2

    _str_to_flag = {
        'NONE': NONE,
        'CONF': CONF,
        'READONLY': READONLY
    }

    @staticmethod
    def fromStr(str_flag):
        if str_flag not in RegFlag._str_to_flag:
            return 0
        return RegFlag._str_to_flag[str_flag]

    @staticmethod
    def fromList(flags) -> int:
        res_flags = 0
        for str_flag in flags:
            flag = RegFlag.fromStr(str_flag)
            res_flags = res_flags | flag
        return res_flags


class RegEFlag:
    NONE = 0x0
    RL_HIDE = 0x1
    CO_HIDE = 0x2
    CO_COUNT = 0x4
    RESERVED = 0x8
    CON_CNT_NMT = 0x10
    CON_CNT_EM = 0x20
    CON_CNT_SYNC = 0x40
    CON_CNT_SYNC_PROD = 0x80
    CON_CNT_STORAGE = 0x100
    CON_CNT_TIME = 0x200
    CON_CNT_EM_PROD = 0x400
    CON_CNT_HB_CONS = 0x800
    CON_CNT_HB_PROD = 0x1000
    CON_CNT_SDO_SRV = 0x2000
    CON_CNT_SDO_CLI = 0x4000
    CON_CNT_RPDO = 0x8000
    CON_CNT_TPDO = 0x10000
    CO_SDO_R = 0x20000
    CO_SDO_W = 0x40000
    CO_TPDO = 0x80000
    CO_RPDO = 0x100000
    CO_TSRDO = 0x200000
    CO_RSRDO = 0x400000


class RegObject:

    objectType: int
    name: str
    description: str
    parent: "RegEntry" or None

    def __init__(self):
        self.name = ""
        self.description = ""
        self.parent = None

    def __repr__(self):
        return f"RegObject({self.name})"


class RegVar(RegObject):

    subIndex: int
    dataType: int
    memAddr: str
    count: int
    minValue: str
    maxValue: str
    defValue: str
    flags: int
    eflags: int
    baseIndex: int
    baseSubIndex: int

    def __init__(self):
        super().__init__()
        self.objectType = ObjectType.VAR
        self.subIndex = 0
        self.dataType = 0
        self.memAddr = ""
        self.count = 1
        self.minValue = ""
        self.maxValue = ""
        self.defValue = ""
        self.flags = 0
        self.eflags = 0
        self.baseIndex = 0
        self.baseSubIndex = 0

    def __repr__(self):
        return f"RegVar({self.subIndex}, {self.name}, {self.memAddr})"


class RegEntry(RegObject):

    index: int
    regVars: list[RegVar]

    def __init__(self):
        super().__init__()
        self.index = 0
        self.regVars = []

    def addVar(self, v: RegVar):
        v.parent = self
        self.regVars.append(v)

    def delVar(self, v: RegVar):
        if v in self.regVars:
            v.parent = None
            self.regVars.remove(v)

    def __repr__(self):
        return f"RegEntry({self.index: X}, {self.name}, {len(self.regVars)})"


