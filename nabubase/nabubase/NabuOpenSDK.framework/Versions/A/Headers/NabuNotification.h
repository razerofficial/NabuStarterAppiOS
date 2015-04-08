//
//  NabuNotification.h
//  RazerSynapseSDK
//
//  Created by Razer on 11/3/14.
//  Copyright (c) 2014 Razer. All rights reserved.
//

#import <Foundation/Foundation.h>

/*!
 @class NabuNotification
 @abstract  A class that defines the Nabu notification
 @discussion
    @param  iconResId       Icon Resource ID
    @param  text            Notification centered text string (use when only one line) (depreciated use message)
    @param  text1           Notification top text string (use when more than one line) (depreciated use message)
    @param  text2           Notification bottom text string (use when more than one line) (depreciated use message)
    @param  status          Notification status (depreciated)
    @param  message         Notification message text. Display up to 2 lines separated by standard new line deliminator '\\n'
 */


@interface NabuNotification : NSObject

@property (copy, nonatomic) NSString *iconResId;
@property (copy, nonatomic) NSString *text DEPRECATED_MSG_ATTRIBUTE("Will be removed in future version. Use message");
@property (copy, nonatomic) NSString *text1 DEPRECATED_MSG_ATTRIBUTE("Will be removed in future version. Use message");
@property (copy, nonatomic) NSString *text2 DEPRECATED_MSG_ATTRIBUTE("Will be removed in future version. Use message");
@property (copy, nonatomic) NSString *status DEPRECATED_MSG_ATTRIBUTE("Will be removed in future version.");
@property (copy, nonatomic) NSString *message;

@end
