//
//  PThreadHandler.h
//  Pods
//
//  Created by ben3 on 06/07/2020.
//

#ifndef PThreadHandler_h
#define PThreadHandler_h

#import <ChatSDK/PThread_.h>
#import <ChatSDK/PMessage.h>
#import <RXSwift/RXSwift-Swift.h>


@protocol PThreadHandler <NSObject>

/**
 * @brief This method invites adds the users provided to a a conversation thread
 * Register block to:
 * - Handle thread creation
 */

-(RXPromise *) createThreadWithUsers: (NSArray *) users
                                name: (NSString *) name
                                type: (bThreadType) type
                         forceCreate: (BOOL) force
                       threadCreated: (void(^)(NSError * error, id<PThread> thread)) threadCreated;

-(RXPromise *) createThreadWithUsers: (NSArray *) users
                                name: (NSString *) name
                         forceCreate: (BOOL) force
                       threadCreated: (void(^)(NSError * error, id<PThread> thread)) threadCreated;

-(RXPromise *) createThreadWithUsers: (NSArray *) users
                                name: (NSString *) name
                       threadCreated: (void(^)(NSError * error, id<PThread> thread)) threadCreated;

-(RXPromise *) createThreadWithUsers: (NSArray *) users
                       threadCreated: (void(^)(NSError * error, id<PThread> thread)) thread;

-(id<PThread>) fetchThreadWithUsers: (NSArray *) users;
-(id<PThread>) fetchOrCreateThreadWithUsers: (NSArray *) users name: (NSString *) name;

/**
 * @brief Add users to a thread
 */
-(RXPromise *) addUsers: (NSArray *) userIDs toThread: (id<PThread>) threadModel;

/**
 * @brief Remove users from a thread
 */
-(RXPromise *) removeUsers: (NSArray *) userIDs fromThread: (id<PThread>) threadModel;

/**
 * @brief Lazy loading of messages this method will load
 * that are not already in memory
 */
-(RXPromise *) loadMoreMessagesFromDate: (NSDate *) date forThread: (id<PThread>) threadModel;
-(RXPromise *) loadMoreMessagesFromDate: (NSDate *) date forThread: (id<PThread>) threadModel fromServer: (BOOL) fromServer;

/**
 * @brief This method deletes an existing thread. It deletes the thread from memory
 * and removes the user from the thread so the user no longer recieves notifications
 * from the thread
 */
-(RXPromise *) deleteThread: (id<PThread>) thread;
-(RXPromise *) leaveThread: (id<PThread>) thread;
-(RXPromise *) joinThread: (id<PThread>) thread;


/**
 * @brief Send different types of message to a particular thread
 */
-(RXPromise *) sendMessageWithText: (NSString *) text withThreadEntityID: (NSString *) threadID;

/**
 * @brief Send different types of message to a particular thread with meta data for the message
 */
-(RXPromise *) sendMessageWithText:(NSString *)text withThreadEntityID:(NSString *)threadID withMetaData: (NSDictionary *)meta;

/**
 * @brief Send a message object
 */
-(RXPromise *) sendMessage: (id<PMessage>) messageModel;

// TODO: Consider making this a PThread for consistency
/**
 * @brief Get the messages for a particular thread
 */
-(NSArray *) messagesForThreadWithEntityID:(NSString *) entityID order: (NSComparisonResult) order;

/**
 * @brief Get a list of all threads
 */
-(NSArray *) threadsWithType: (bThreadType) type;
-(NSArray *) threadsWithType:(bThreadType)type includeDeleted: (BOOL) includeDeleted;
-(NSArray<PThread> *) threadsWithType:(bThreadType)type includeDeleted: (BOOL) includeDeleted includeEmpty: (BOOL) includeEmpty;

-(void) sendLocalSystemMessageWithText:(NSString *)text withThreadEntityID:(NSString *)threadID;
-(void) sendLocalSystemMessageWithText:(NSString *)text type: (bSystemMessageType) type withThreadEntityID:(NSString *)threadID;

- (NSArray *)threadsWithUsers:(NSArray *)users type:(bThreadType)type;

- (RXPromise *) deleteMessage: (NSString *)messageID;

-(BOOL) canDeleteMessage: (id<PMessage>) message;

-(RXPromise *) replyToMessage: (id<PMessage>) message withThreadID: (NSString *) threadEntityID reply: (NSString *) reply;
-(RXPromise *) forwardMessage: (id<PMessage>) message toThreadWithID: (NSString *) threadEntityID;

// Permissions
-(BOOL) rolesEnabled: (NSString *) threadEntityID;
-(RXPromise *) role: (NSString *) threadEntityID forUser: (NSString *) userEntityID;
-(RXPromise *) canDelete: (NSString *) threadEntityID;

@optional

-(RXPromise *) muteThread: (id<PThread>) thread;
-(RXPromise *) unmuteThread: (id<PThread>) thread;
-(RXPromise *) destroyThread: (id<PThread>) thread;

@end

#endif /* PThreadHandler_h */
