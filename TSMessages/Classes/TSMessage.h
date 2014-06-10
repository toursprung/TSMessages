//
//  TSMessage.h
//  Felix Krause
//
//  Created by Felix Krause on 24.08.12.
//  Copyright (c) 2012 Felix Krause. All rights reserved.
//

#import <UIKit/UIKit.h>

@class TSMessageView;

typedef NS_ENUM(NSInteger, TSMessageType) {
    TSMessageTypeDefault = 0,
    TSMessageTypeSuccess,
    TSMessageTypeWarning,
    TSMessageTypeError
};

typedef NS_ENUM(NSInteger, TSMessagePosition) {
    TSMessagePositionTop = 0,
    TSMessagePositionBottom
};

typedef NS_ENUM(NSInteger, TSMessageDuration) {
    TSMessageDurationAutomatic = 0,
    TSMessageDurationEndless = -1, // The message is displayed until the user dismissed it or it is dismissed by calling dismissCurrentMessage
};

typedef void (^TSMessageCallback)(TSMessageView *messageView);

@class TSMessage;
/** The TSMessageDelegate protocol defines optional methods for performing actions before a message is displayed, and after a message is fully displayed. It also
    allows for actions after a message is dismissed, either by the user or after its defined duration.
*/
@protocol TSMessageDelegate <NSObject>
@optional
/** Allows additional actions to be performed prior to displaying a notification. */
- (void)willDisplayNotification:(TSMessageView *)notification;
/** Allows additional actions to be performed after a notification is fully displayed. */
- (void)didDisplayNotification:(TSMessageView *)notification;
/** Allows additional actions to be performed after a notification is dismissed. */
- (void)didDismissNotification:(TSMessageView *)notification;

@end

@interface TSMessage : NSObject

@property (strong, nonatomic) id <TSMessageDelegate> delegate;

+ (instancetype)sharedMessage;

+ (UIViewController *)defaultViewController;

/** Returns a message view for further customization

 @param title The title of the message view
 @param subtitle The text that is displayed underneath the title
 @param type The message type (Default, Warning, Error, Success)

 @return The message view
 */
+ (TSMessageView *)messageWithTitle:(NSString *)title
                           subtitle:(NSString *)subtitle
                               type:(TSMessageType)type;

/** Displays a message right away and returns the message view

 @param title The title of the message view
 @param subtitle The text that is displayed underneath the title
 @param type The message type (Default, Warning, Error, Success)

 @return The message view
 */
+ (TSMessageView *)displayMessageWithTitle:(NSString *)title
                                  subtitle:(NSString *)subtitle
                                      type:(TSMessageType)type;

/** Returns a message view in a specific view controller for further customization

 @param title The title of the message view
 @param subtitle The message that is displayed underneath the title (optional)
 @param image A custom icon image (optional)
 @param type The message type (Default, Warning, Error, Success)
 @param viewController The view controller to display the message in

 @return The message view
 */
+ (TSMessageView *)messageWithTitle:(NSString *)title
                           subtitle:(NSString *)subtitle
                              image:(UIImage *)image
                               type:(TSMessageType)type
                   inViewController:(UIViewController *)viewController;

/** Displays a message right away in a specific view controller and returns
 the message view

 @param title The title of the message view
 @param subtitle The text that is displayed underneath the title
 @param image A custom icon image (optional)
 @param type The message type (Default, Warning, Error, Success)
 @param viewController The view controller to display the message in

 @return The message view
 */
+ (TSMessageView *)displayMessageWithTitle:(NSString *)title
                                  subtitle:(NSString *)subtitle
                                     image:(UIImage *)image
                                      type:(TSMessageType)type
                          inViewController:(UIViewController *)viewController;

/** Use this method to set a default view controller to display the messages in */
+ (void)setDefaultViewController:(UIViewController *)defaultViewController;

/** Use this method to use custom designs for your messages. */
+ (void)addCustomDesignFromFileWithName:(NSString *)fileName;

/** Dismisses the current message. If another message is in the queue,
 it will be displayed automatically after the current one is dismissed.

 @return YES if the current message was successfully dismissed.
 NO if there is no current message to be dismissed.
 */
+ (BOOL)dismissCurrentMessage;

/** Dismisses the current message even if it is not fully displayed, yet.
 If another message is in the queue, it will be displayed automatically
 after the current one is dismissed.
 
 @return YES if the current message was successfully dismissed.
 NO if there is no current message to be dismissed.
 */
+ (BOOL)dismissCurrentMessageForce:(BOOL)force;

/** Indicates whether a message is currently being displayed.

 @return YES if a message is currently being displayed.
         NO if no message is currently being displayed.
 */
+ (BOOL)isDisplayingMessage;

/** Displays or enqueues the message view. If there is a message
 displayed currently, the message view gets added to the end of the
 queue and displayed after its prior messages are displayed.
 If it is the only message it gets displayed right away.
 */
+ (void)displayOrEnqueueMessage:(TSMessageView *)messageView;

/** Displays a permanent message.

 This differs from normal message in that permanent messages are not
 contained in the messages queue and can be displayed in addition to the
 other messages.

 Permanent messages do not get dismissed automatically, hence they do
 not have a duration but have to be dismissed by the user or programmatically
 in one of the callbacks.
 */
+ (void)displayPermanentMessage:(TSMessageView *)messageView;

@end
