struct rectangle
{
    vec2 pos;
    vec2 bounding;
};
    
vec4 drawRectangle(vec2 uv, rectangle targetRect, vec3 color)
{
    float alpha = 1.0;
    
    if (uv.x < targetRect.pos.x || uv.x >= targetRect.pos.x + targetRect.bounding.x) alpha = 0.0;
    if (uv.y < targetRect.pos.y || uv.y >= targetRect.pos.y + targetRect.bounding.y) alpha = 0.0;
    
    return vec4(color, alpha);
}

vec3 rgbToDecimal(float r, float g, float b)
{
    return vec3(r / 255.0, g / 255.0, b / 255.0);
}

vec4 drawMaxilla(vec2 uv, vec2 pos, float skullUnit, vec3 skullColour)
{
    float alpha = 0.0;
    
    if (uv.x - pos.x - (30.0 * skullUnit) <= uv.y - pos.y
        && uv.y < pos.y - 30.0 * skullUnit
        && uv.y > pos.y - 40.0 * skullUnit
        && uv.x > pos.x - 60.0 * skullUnit) alpha = 1.0;
    if (uv.x - pos.x + (30.0 * skullUnit) >= iResolution.y - uv.y - pos.y
        && uv.y < pos.y - 30.0 * skullUnit
        && uv.y > pos.y - 40.0 * skullUnit
        && uv.x < pos.x + 60.0 * skullUnit) alpha = 1.0;

    return vec4(skullColour, alpha);
}

vec4 drawSkull(vec2 uv, vec2 pos, vec3 skullColour)
{
    vec4        skullVec                            = vec4(0.0, 0.0, 0.0, 0.0);
    float       skullWidth                          = 0.25 * iResolution.x;
    float       skullUnit                           = skullWidth / 256.0;
    const int   skullComponentSize                  = 5;
    rectangle   skullComponents[skullComponentSize];
    
    skullComponents[0].bounding = vec2(120.0 * skullUnit, 50.0 * skullUnit);
    skullComponents[0].pos = pos - vec2(skullComponents[0].bounding.x / 2.0, 0.0);
    
    skullComponents[1].bounding = vec2(20.0 * skullUnit, 30.0 * skullUnit);
    skullComponents[1].pos = pos - vec2(60.0 * skullUnit, 30.0 * skullUnit);

    skullComponents[2].bounding = vec2(20.0 * skullUnit, 30.0 * skullUnit);
    skullComponents[2].pos = pos - vec2(10.0 * skullUnit, 30.0 * skullUnit);
    
    skullComponents[3].bounding = vec2(20.0 * skullUnit, 30.0 * skullUnit);
    skullComponents[3].pos = pos - vec2(-40.0 * skullUnit, 30.0 * skullUnit);
    
    skullComponents[4].bounding = vec2(60.0 * skullUnit, 15.0 * skullUnit);
    skullComponents[4].pos = pos - vec2(30.0 * skullUnit, 55.0 * skullUnit);

    for (int i = 0; i < skullComponentSize; i++)
    {
        skullVec += drawRectangle(uv, skullComponents[i], skullColour);
    }
    
    skullVec += drawMaxilla(uv, pos, skullUnit, skullColour);

    return skullVec;
}


void main(void)
{
    vec2 uv = gl_FragCoord.xy;
    vec2 centre = iResolution.xy * 0.5;

    vec2 backgrounduv = gl_FragCoord.xy / iResolution.xy;
    vec4 background = vec4(backgrounduv,0.5+0.5*sin(iGlobalTime),1.0);
    vec4 skullVec = drawSkull(uv, centre, rgbToDecimal(255.0, 255.0, 255.0));
    
    gl_FragColor = mix(background, skullVec, skullVec.a);

}