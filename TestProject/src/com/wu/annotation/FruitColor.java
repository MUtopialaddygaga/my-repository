package com.wu.annotation;

import java.lang.annotation.Documented;
import java.lang.annotation.ElementType;
import java.lang.annotation.Retention;
import java.lang.annotation.RetentionPolicy;
import java.lang.annotation.Target;

/**
 * @description 2017-8-11下午3:00:05 @
 */
@Target(ElementType.FIELD)
@Retention(RetentionPolicy.RUNTIME)
@Documented
public @interface FruitColor {

    /*
     * 颜色
     */
    public enum Color {
        BLUE, RED, GREEN
    };

    /*
     * 
     * 颜色属性
     */
    Color fruitColor() default Color.GREEN;
}
