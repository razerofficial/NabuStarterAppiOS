//
//  NabuDataManager.h
//  RazerSynapseSDK
//
//  Created by Razer on 11/3/14.
//  Copyright (c) 2014 Razer. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "NabuOpenSDKConstants.h"

typedef void (^NabuCompletionBlock)(NSDictionary * data);

@class NabuNotification;


/**
 *  The NabuDataManager class is responsible for all interactions between the NabuSDK and the NabuAPI.
 */
@interface NabuDataManager : NSObject



/**
*  This is a singleton instance of the Nabu Data Manager
*
*  @return Returns shared data manager
*/
+ (id) sharedDataManager;



/**
 *  This method will construct a URL using the formatted information from client app ID, scope and URL scheme callback.
 *
 *  @param appId          Your client's App ID
 *  @param appScope       Your client's Scope upon registration - (e.g fitness)
 *  @param appURICallback Your client's custom defined URL scheme for app to app communication. Must be the root scheme. (i.e., DASOrg). Note: Do NOT append anything to the end of the callback URI.
 *
 *  @return A URL to call to request authorization for access to Nabu SDK.
                - Example:

                        NSURL *authorizationURL = [[RzDataManager sharedDataManager] authorizationURLForAppID:@"ABC123ABC123"
                                                                                                     andScope:@"fitness"
                                                                                     withAppURISchemeCallback:@"DASOrg"
 
                        [[UIApplication sharedApplication] openURL:authorizationURL];
 */
- (NSURL *) authorizationURLForAppID:(NSString *)appId
                            andScope:(NSString *)appScope
            withAppURISchemeCallback:(NSString *)appURICallback;



/**
 *  Validate Response from Nabu Utility Application Authentication request
 *
 *  @param urlResponse This parameter is a Base64 encoded string which is composed of Refresh Token, Access Token and other information that are returned from the Razer Nabu Utility after authorization.
 */
- (void) validateURLResponse:(NSURL *)urlResponse
                   withBlock:(NabuCompletionBlock)blk;


/**
 *  Check authorization status of your application.
 *
 *  Deprecated - Use checkAppAuthorizationStatusWithCompletion: instead.
 *
 *  @param blk Returns: kRefreshAuthorizationTokenFailed = 0, kRefreshAuthorizationTokenSuccess = 1 or kOperationPermissionDenied = 9999
 */
- (void) checkAppAuthorizedWithBlock:(NabuCompletionBlock)blk DEPRECATED_MSG_ATTRIBUTE("Use checkAppAuthorizationStatusWithCompletion:");

/**
 *  Check current authorization status of your application.
 *  
 *  @param completion Returns: status as kRefreshAuthorizationTokenFailed = 0, kRefreshAuthorizationTokenSuccess = 1 or kOperationPermissionDenied = 9999
 */
-(void)checkAppAuthorizationStatusWithCompletion:(void(^)(AuthenticationStatus status, NSError *error))completion;

/**
 *  This will query the list of bands that is associated to the user's razer account.
 *  Deprecated - Use getNabuBandListWithCompletion: instead.
 */
- (void)getBandListWithBlock:(NabuCompletionBlock)blk DEPRECATED_MSG_ATTRIBUTE("Use getNabuBandListWithCompletion:");

/**
 *  This will check with the NabuAPI and return an array of NabuBand objects for all bands associated with the user's account.
 *
 */
-(void)getNabuBandListWithCompletion:(void (^)(NSArray *arrayOfNabuBands, NSError *error))completion;

/**
 *  Retrieve fitness data from NabuAPI. Request fitness data based on the last set of records.
 *  Deprecated - Use getFitnessDataFor:withCompletion:
 *  @param numberOfRecords For the number of records, the user can request up to 7 days or 168 hours (i.e, no_of_records = 2016) of historical data
            - Example:
 
                    If you wanted to get 2016 records of fitness data:
 
                    [[NabuDataManager sharedDataManager] getFitnessDataWithNumberOfRecords:@"2016"];
 */

- (void) getFitnessDataWithNumberOfRecords:(NSString *)numberOfRecords
                                 withBlock:(NabuCompletionBlock)blk DEPRECATED_MSG_ATTRIBUTE("Use getFitnessDataFor:withCompletion:");

/**
 *  Retrieve fitness data from NabuAPI. Request fitness data based on the last set of records.
 *
 *  @param numberOfRecords For the number of records, the user can request up to 7 days or 168 hours (i.e, no_of_records = 2016) of historical data
 - Example:
 
 If you wanted to get 2016 records of fitness data:
 
 [[NabuDataManager sharedDataManager] getFitnessDataFor:2016 withCompletion:(void (^)(NSArray *arrayOfNabuFitnessData))completion];
 */

-(void)getFitnessDataFor:(NSInteger)numberOfRecords
          withCompletion:(void (^)(NSArray *arrayOfNabuFitnessData, NSError *error))completion;


/**
 *  Retrieve fitness data from NabuAPI. Request fitness data based on a given date.
 *
 *  @param date The format for the date should be in Unix Timestamp (Epoch time).
            - Example:
 
                    If you wanted to get the fitness data for date (Mon, 02 Jun 2014 11:49:18 GMT), you would say:
 
                    [[NabuDataManager sharedDataManager] getFitnessDataByDate:@"1401709762" withBlock:blk];
 */

- (void) getFitnessDataByDate:(NSString *)date
                    withBlock:(NabuCompletionBlock)blk DEPRECATED_MSG_ATTRIBUTE("Use getFitnessDataForDate:toDate:withCompletion:");


/**
 *  Retrieve fitness data from NabuAPI. Request fitness data based on a given start and end time.
 *
 *  @param startTime Start time of your query. This value must be in Unix Timestamp format (Epoch time).
 *  @param endTime   End time of your query. This value must be in Unix Timestamp format (Epoch time).
 - Example:
 
 Start Time is Fri, 14 Mar 2014 06:52:22 GMT
 End Time is Mon, 24 Mar 2014 06:52:22 GMT
 
 [[NabuDataManager sharedDataManager] getFitnessDataWithStartTime:@"1394779942" endTime:@"1395643942" withBlock:blk];
 */

- (void) getFitnessDataWithStartTime:(NSString *)startTime
                             endTime:(NSString *)endTime
                           withBlock:(NabuCompletionBlock)blk DEPRECATED_MSG_ATTRIBUTE("Use getFitnessDataForDate:toDate:withCompletion:");

/**
 *  Retrieve fitness data from NabuAPI. endDateInEpoch is optional use 0 if not using, not specifying this will result in all fitnessData for a given day. Request fitness data based on a given start and end time.
 *
 *  @param dateInEpoch Start time of your query. This value must be in Unix Timestamp format (Epoch time).
 *  @param endDateInEpoch   End time of your query. This value must be in Unix Timestamp format (Epoch time).
 - Example:
 
  - Request data for this period
 Start Time is Fri, 14 Mar 2014 06:52:22 GMT
 End Time is Mon, 24 Mar 2014 06:52:22 GMT
 
 [[NabuDataManager sharedDataManager] getFitnessDataForDate:1394779942 toDate:1395643942 withCompletion:blk];
 
 or
 
 - Request all data for this day
 Start Time is Fri, 14 Mar 2014 06:52:22 GMT
 [[NabuDataManager sharedDataManager] getFitnessDataForDate:1394779942 toDate:0 withCompletion:blk];
 

 */
-(void)getFitnessDataForDate:(NSInteger)dateInEpoch
                      toDate:(NSInteger)endDateInEpoch
              withCompletion:(void(^)(NSArray *arrayOfNabuFitnessData, NSError *error))completion;





/**
 *  Retrieve historical fitness data from NabuAPI. Request fitness history for a given number of days. The server returns the aggregated data (steps/floors/calories/distances) for each day.
 *
 *  @param numberOfDays For the number of days, the user can request up to 12 months (i.e., days = 370) of historical data.
            - Example:
 
                    If you want to get fitness history data for the past 100 days:
 
                    [[NabuDataManager sharedDataManager] getFitnessHistoryDataForNumberOfDays:@"100"];
 */
- (void) getFitnessHistoryDataForNumberOfDays:(NSString *)numberOfDays
                                    withBlock:(NabuCompletionBlock)blk DEPRECATED_MSG_ATTRIBUTE("Use getFitnessHistoryForNumberOfDays:withCompletion:");


/**
 *  Retrieve historical fitness data from NabuAPI. Request fitness history for a given number of days. The server returns the aggregated data (steps/floors/calories/distances) for each day.
 *
 *  @param numberOfDays For the number of days, the user can request up to 12 months (i.e., days = 370) of historical data.
 - Example:
 
 If you want to get fitness history data for the past 100 days:
 
 [[NabuDataManager sharedDataManager] getFitnessHistoryForNumberOfDays:100 withCompletion:blk];
 */
-(void)getFitnessHistoryForNumberOfDays:(NSInteger)numberOfDays
                         withCompletion:(void(^)(NSArray *arrayOfNabuFitnessHistoryDataObjects, NSError *error))completion;


/**
 *  Retrieve historical fitness data from NabuAPI. Request fitness history based on a given start and end time. The server returns the aggregated data (steps/floors/calories/distances) for each day.
 *
 *  @param startTime Start time of your query. This value must be in Unix Timestamp format (Epoch time).
 *  @param endTime   End time of your query. This value must be in Unix Timestamp format (Epoch time).
             - Example:
             
                     Start Time is Fri, 14 Mar 2014 06:52:22 GMT
                     End Time is Mon, 24 Mar 2014 06:52:22 GMT
                     
                     [[NabuDataManager sharedDataManager] getFitnessHistoryDataWithStartTime:@"1394779942" endTime:@"1395643942" withBlock:blk];
 */
- (void) getFitnessHistoryDataWithStartTime:(NSString *)startTime
                                    endTime:(NSString *)endTime
                                  withBlock:(NabuCompletionBlock)blk  DEPRECATED_MSG_ATTRIBUTE("Use getFitnessHistoryDataForStartTime:endTime:withCompletion");

/**
 *  Retrieve historical fitness data from NabuAPI. Request fitness history based on a given start and end time. The server returns the aggregated data (steps/floors/calories/distances) for each day.
 *
 *  @param startTime Start time of your query. This value must be in Unix Timestamp format (Epoch time).
 *  @param endTime   End time of your query. This value must be in Unix Timestamp format (Epoch time).
 - Example:
 
 Start Time is Fri, 14 Mar 2014 06:52:22 GMT
 End Time is Mon, 24 Mar 2014 06:52:22 GMT
 
 [[NabuDataManager sharedDataManager] getFitnessHistoryDataForStartTime:@"1394779942" endTime:@"1395643942" withCompletion:blk];
 */
-(void)getFitnessHistoryDataForStartTime:(NSInteger)epochStartTime
                                 endTime:(NSInteger)epochEndTime
                          withCompletion:(void(^)(NSArray *arrayOfNabuFitnessHistoryDataObjects, NSError *error))completion;


/**
 *  Retrieve sleep data from NabuAPI. Request sleep data based on a given start and end time.
 *
 *  @param startTime Start time of your query. This value must be in Unix Timestamp format (Epoch time).
 *  @param endTime   End time of your query. This value must be in Unix Timestamp format (Epoch time).
            - Example:
        
                    Start Time is Fri, 14 Mar 2014 06:52:22 GMT
                    End Time is Mon, 24 Mar 2014 06:52:22 GMT
 
                    [[NabuDataManager sharedDataManager] getSleepTrackerDataWithStartTime:@"1394779942" endTime:@"1395643942"];
 */
- (void) getSleepTrackerDataWithStartTime:(NSString *)startTime
                                  endTime:(NSString *)endTime
                                withBlock:(NabuCompletionBlock)blk DEPRECATED_MSG_ATTRIBUTE("Use getSleepTrackerDataWithStartTime:endTime:withCompletion:");


/**
 *  Retrieve sleep data from NabuAPI. Request sleep data based on a given start and end time.
 *
 *  @param startTime Start time of your query. This value must be in Unix Timestamp format (Epoch time).
 *  @param endTime   End time of your query. This value must be in Unix Timestamp format (Epoch time).
 *  @param completion Completion block that outputs an array of NabuSleepTrackerData objects.
 - Example:
 
 Start Time is Fri, 14 Mar 2014 06:52:22 GMT
 End Time is Mon, 24 Mar 2014 06:52:22 GMT
 
 [[NabuDataManager sharedDataManager] getSleepTrackerDataWithStartTime:@"1394779942" endTime:@"1395643942" withCompletion:blk];
 */
-(void)getSleepTrackerDataWithStartTime:(NSInteger)epochStartTime
                                endTime:(NSInteger)epochEndTime
                         withCompletion:(void(^)(NSArray *arrayOfSleepTrackerDataObjects, NSError *error))completion;

/**
 *  Retrieve historical sleep data from NabuAPI. Request sleep history for a given number of days. The server returns the aggregated data for each day.
 *
 *  @param numberOfDays For the number of days, the user can request up to 12 months (i.e., days = 370) of historical data.
            - Example:
 
                    Number of Days = 370
 
                    [[NabuDataManager sharedDataManager] getSleepHistoryDataWithNumberOfDays:@"370"];
 */
- (void) getSleepHistoryDataWithStartTime:(NSString *)numberOfDays
                                withBlock:(NabuCompletionBlock)blk DEPRECATED_MSG_ATTRIBUTE("Use getSleepHistoryDataWithNumberOfDays:withCompletion:");

/**
 *  Retrieve historical sleep data from NabuAPI. Request sleep history for a given number of days. The server returns the aggregated data for each day.
 *
 *  @param numberOfDays For the number of days, the user can request up to 12 months (i.e., days = 370) of historical data.
 *  @param completion Completion block that outputs an array of NabuSleepHistoryData objects.
     - Example:
     
            Number of Days = 370
     
            [[NabuDataManager sharedDataManager] getSleepHistoryDataWithNumberOfDays:370" withCompletion:blk];
 */
-(void)getSleepHistoryDataWithNumberOfDays:(NSInteger)numberOfDays
                            withCompletion:(void(^)(NSArray *arrayOfNabuSleepHistoryDataObjects, NSError *error))completion;


/**
 *  Retrieve historical sleep data from NabuAPI. Request sleep history based on a given start and end time. The server returns the aggregated data for each day.
 *
 *  @param startTime Start time of your query. This value must be in Unix Timestamp format (Epoch time).
 *  @param endTime   End time of your query. This value must be in Unix Timestamp format (Epoch time).
             - Example:
             
                     Start Time is Fri, 14 Mar 2014 06:52:22 GMT
                     End Time is Mon, 24 Mar 2014 06:52:22 GMT
 
 [[NabuDataManager sharedDataManager] getSleepHistoryDataWithStartTime:@"1394779942" endTime:@"1395643942" withBlock:blk];
 */
- (void) getSleepHistoryDataWithStartTime:(NSString *)startTime
                                  endTime:(NSString *)endTime
                                withBlock:(NabuCompletionBlock)blk DEPRECATED_MSG_ATTRIBUTE("Use getSleepHistoryDataWithNumberOfDays:withCompletion:");


/**
 *  Retrieve historical sleep data from NabuAPI. Request sleep history based on a given start and end time. The server returns the aggregated data for each day.
 *
 *  @param startTime Start time of your query. This value must be in Unix Timestamp format (Epoch time).
 *  @param endTime   End time of your query. This value must be in Unix Timestamp format (Epoch time).
 - Example:
 
 Start Time is Fri, 14 Mar 2014 06:52:22 GMT
 End Time is Mon, 24 Mar 2014 06:52:22 GMT
 
 [[NabuDataManager sharedDataManager] getSleepHistoryDataWithStartTime:1394779942 endTime:1395643942 withCompletion];
 */
-(void)getSleepHistoryDataWithStartTime:(NSInteger)startTime
                                endTime:(NSInteger)endTime
                         withCompletion:(void(^)(NSArray *arrayOfNabuSleepHistoryDataObjects, NSError *error))completion;


/**
 *  Retrieve Hi Five data from NabuAPI. Use this method to identify any Hi Five requests that the Nabu Band has made within a given date range.
 *  You can request up to 7 Days worth of data.
 *
 *  @param startTime Start time of your query. This value must be in Unix Timestamp format (Epoch time).
 *  @param endTime   End time of your query. This value must be in Unix Timestamp format (Epoch time).
            - Example:

                    Start Time is Fri, 14 Mar 2014 06:52:22 GMT
                    End Time is Mon, 24 Mar 2014 06:52:22 GMT

                    [[NabuDataManager sharedDataManager] getHiFiveDataWithStartTime:@"1394779942" endTime:@"1395643942"];
 */
- (void) getHiFiveDataWithStartTime:(NSString *)startTime
                            endTime:(NSString *)endTime
                          withBlock:(NabuCompletionBlock)blk;

//-(void)getHandshakeDataWithStartTime:(NSInteger)startTime endTime:(NSInteger)endtime withCompletion:(void(^)(NS))


/**
 *  Request Pulse data for all nearby Nabu bands. Use this method to identify all Pulse data that the bands have made within a given date range.
 *
 *  @param startTime Start time of your query. This value must be in Unix Timestamp format (Epoch time).
 *  @param endTime   End time of your query. This value must be in Unix Timestamp format (Epoch time).
            - Example:

                    Start Time is Fri, 14 Mar 2014 06:52:22 GMT
                    End Time is Mon, 24 Mar 2014 06:52:22 GMT

                    [[NabuDataManager sharedDataManager] getPulseDataWithStartTime:@"1394779942" endTime:@"1395643942"];
 */
- (void) getPulseDataWithStartTime:(NSString *)startTime
                           endTime:(NSString *)endTime
                         withBlock:(NabuCompletionBlock)blk;


/**
 *  Request the current user's profile information from NabuAPI. Note that certain information is available using this call. If you want all the information, you can get it through the Razer Nabu Utility App.
            - The NabuUserProfile object contains:
 
                        NSString *nickName;
                        NSString *avatar;
                        NSString *birthDay;
                        NSString *birthMonth;
                        NSString *birthYear;
                        NSString *gender;
                        NSString *height;
                        NSString *weight;
                        NSString *unit;
 */
- (void) getUserProfileWithBlock:(NabuCompletionBlock)blk;


/**
 *  Send notifications to the band from your app.
 *
 *  @param notificationObj A Nabu Notification Object.

             - Example:
 
                    NabuNotification *nabuNotification = [[NabuNotification alloc] init];
 
                    nabuNotification.message = @"Hello World.\n This is for testing only.";
                    nabuNotification.iconResId = @"smiley";
 
                    [[NabuDataManager sharedDataManager] sendNotificationToBand:nabuNotification];
 
 */
- (void) sendNotificationToBand:(NabuNotification *)notificationObj withBlock:(NabuCompletionBlock)blk;


/**
 *  Create/update your own clipboard.
 *
 *  @param message      Maximum length of 140 characters.
 *  @param publicData   Binary/text data with maximum size of 2KB. \n
                        This data can be read by other users.
 *  @param privateData  Binary/text data with maximum size of 2KB. \n
                        This data can only be read/updated by the owner.
 */
- (void) createUpdateMyClipboardWithMessage:(NSString *)message
                                 publicData:(NSData *)publicData
                                privateData:(NSData *)privateData
                                  withBlock:(NabuCompletionBlock)blk;


/**
 *  Delete your own clipboard.
 *
 */
- (void) deleteMyClipboardWithBlock:(NabuCompletionBlock)blk;


/**
 *  Get your own clipboard.
 *
 */
- (void) getMyClipboardWithBlock:(NabuCompletionBlock)blk;


/**
 *  Get other users clipboards.
 *
 *  @param openIds  Array of openIDs.
                    Limited to a maximum 20 openIDs per query.
 */
- (void) getClipboardsWithOpenIds:(NSArray *)openIds withBlock:(NabuCompletionBlock)blk;

@end
