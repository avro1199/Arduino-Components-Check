// Convert RC (1000..2000) to speed
static int rcToSpeed(int rc)
{
    rc = constrain(rc, RC_MIN, RC_MAX);
    int d = rc - RC_MID;
    if (abs(d) < RC_DEADBAND)
        return 0;

    return map(rc, RC_MIN, RC_MAX, -((int)TOP_SPEED), (int)TOP_SPEED);
}