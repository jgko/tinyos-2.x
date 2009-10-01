configuration HalSam3uRttC
{
    provides
    {
        interface Init;
        interface Alarm<T32khz,uint32_t> as Alarm;
        interface LocalTime<T32khz> as LocalTime;
        interface LocalTime<TMilli> as LocalTimeMilli;
    }
}

implementation
{
    components HplSam3uRttC, HalSam3uRttP;

    HalSam3uRttP.HplSam3uRtt -> HplSam3uRttC;
    HalSam3uRttP.RttInit -> HplSam3uRttC.Init;

    Init = HalSam3uRttP;
    Alarm = HalSam3uRttP;
    LocalTime = HalSam3uRttP.LocalTime;
    LocalTimeMilli = HalSam3uRttP.LocalTimeMilli;
}    


