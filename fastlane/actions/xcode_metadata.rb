# frozen_string_literal: true

module Fastlane
  module Actions
    module SharedValues
      XCODE_METADATA_OS_BUILD = :XCODE_METADATA_OS_BUILD
      XCODE_METADATA_XCODE_VERSION = :XCODE_METADATA_XCODE_VERSION
      XCODE_METADATA_XCODE_VERSION_CODE = :XCODE_METADATA_XCODE_VERSION_CODE
      XCODE_METADATA_XCODE_BUILD = :XCODE_METADATA_XCODE_BUILD
      XCODE_METADATA_SDK_VERSION = :XCODE_METADATA_SDK_VERSION
      XCODE_METADATA_SDK_BUILD = :XCODE_METADATA_SDK_BUILD
      XCODE_METADATA_SDK_PLATFORM_VERSION = :XCODE_METADATA_SDK_PLATFORM_VERSION
    end

    class XcodeMetadataAction < Action
      def self.run(_params)
        os_info = Actions.sh 'sw_vers', log: false
        os_build = os_info.split[-1]
        UI.message "OS build: #{os_build}"
        Actions.lane_context[SharedValues::XCODE_METADATA_OS_BUILD] = os_build

        xcode_info = Actions.sh 'xcodebuild -version', log: false
        xcode_version = xcode_info.split[1]
        xcode_version_code = xcode_version.gsub '.', ''
        xcode_version_code += '0' if xcode_version_code.length < 4
        xcode_build = xcode_info.split[-1]
        UI.message "Xcode version: #{xcode_version}"
        UI.message "Xcode version code: #{xcode_version_code}"
        UI.message "Xcode build: #{xcode_build}"
        Actions.lane_context[SharedValues::XCODE_METADATA_XCODE_VERSION] = xcode_version
        Actions.lane_context[SharedValues::XCODE_METADATA_XCODE_VERSION_CODE] = xcode_version_code
        Actions.lane_context[SharedValues::XCODE_METADATA_XCODE_BUILD] = xcode_build

        sdk_version = Actions.sh 'xcrun -sdk macosx --show-sdk-version', log: false
        sdk_version = sdk_version.strip
        sdk_build = Actions.sh 'xcrun -sdk macosx --show-sdk-build-version', log: false
        sdk_build = sdk_build.strip
        sdk_platform_version = Actions.sh 'xcrun -sdk macosx --show-sdk-platform-version', log: false
        sdk_platform_version = sdk_platform_version.strip
        UI.message "SDK version: #{sdk_version}"
        UI.message "SDK build: #{sdk_build}"
        UI.message "SDK platform version: #{sdk_platform_version}"
        Actions.lane_context[SharedValues::XCODE_METADATA_SDK_VERSION] = sdk_version
        Actions.lane_context[SharedValues::XCODE_METADATA_SDK_BUILD] = sdk_build
        Actions.lane_context[SharedValues::XCODE_METADATA_SDK_PLATFORM_VERSION] = sdk_platform_version
      end

      #####################################################
      # @!group Documentation
      #####################################################

      def self.description
        'Get Xcode metadata'
      end

      def self.details
        'This action gets various metadata.'
      end

      def self.available_options
        []
      end

      def self.output
        [
          ['XCODE_METADATA_OS_BUILD', 'Current OS build'],
          ['XCODE_METADATA_XCODE_VERSION', 'Xcode version'],
          ['XCODE_METADATA_XCODE_VERSION_CODE', 'Xcode version code'],
          ['XCODE_METADATA_XCODE_BUILD', 'Xcode build'],
          ['XCODE_METADATA_SDK_VERSION', 'SDK version'],
          ['XCODE_METADATA_SDK_BUILD', 'SDK build'],
          ['XCODE_METADATA_SDK_PLATFORM_VERSION', 'SDK platform version']
        ]
      end

      def self.authors
        ['@ntadej']
      end

      def self.is_supported?(platform)
        platform == :mac
      end
    end
  end
end
