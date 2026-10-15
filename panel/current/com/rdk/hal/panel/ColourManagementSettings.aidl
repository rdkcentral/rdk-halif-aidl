/*
 * If not stated otherwise in this file or this component's LICENSE file the
 * following copyright and licenses apply:
 *
 * Copyright 2026 RDK Management
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 * http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */
package com.rdk.hal.panel;

/**
 * @brief Grouped colour-management settings.
 *
 * This structure allows clients to update the complete CMS state with a single
 * read-modify-apply cycle instead of issuing separate writes for each colour
 * component. It carries one integer value for each hue, saturation, and
 * luminance slot across the six CMS colours: red, green, blue, yellow, cyan,
 * and magenta.
 */
@VintfStability
parcelable ColourManagementSettings {
    int redHue;
    int redSaturation;
    int redLuminance;
    int greenHue;
    int greenSaturation;
    int greenLuminance;
    int blueHue;
    int blueSaturation;
    int blueLuminance;
    int yellowHue;
    int yellowSaturation;
    int yellowLuminance;
    int cyanHue;
    int cyanSaturation;
    int cyanLuminance;
    int magentaHue;
    int magentaSaturation;
    int magentaLuminance;
}