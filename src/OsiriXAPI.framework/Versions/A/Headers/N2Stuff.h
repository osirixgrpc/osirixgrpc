/*=========================================================================
 Program:   OsiriX
 Copyright (c) 2010 - 2020 Pixmeo SARL
 266 rue de Bernex
 CH-1233 Bernex
 Switzerland
 All rights reserved.
 =========================================================================*/

#ifndef OsiriX_Lion_N2Localization_h
#define OsiriX_Lion_N2Localization_h

#define N2SingularPlural(c, s, p) (c == 1? s : p)
#define N2LocalizedSingularPlural(c, s, p) (c == 1? s : p)

#define N2SingularPluralCount(c, s, p) [NSString stringWithFormat:@"%d %@", (int)c, (c == 1? s : p)]
#define N2LocalizedSingularPluralCount(c, s, p) [NSString stringWithFormat:@"%@ %@", [NSNumberFormatter localizedStringFromNumber:[NSNumber numberWithInteger:(NSInteger)c] numberStyle:NSNumberFormatterDecimalStyle], (c == 1? s : p)]

#define N2LocalizedDecimal(c) [NSNumberFormatter localizedStringFromNumber:[NSNumber numberWithInteger:(NSInteger)c] numberStyle:NSNumberFormatterDecimalStyle]

#endif
