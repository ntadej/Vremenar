module Fastlane
  module Actions
    module SharedValues
      RUN_QMAKE_PROJECT_PATH = :RUN_QMAKE_PROJECT_PATH
    end

    class RunQmakeAction < Action
      def self.run(params)
        UI.message "Build path: #{params[:build_path]}"

        FileUtils.mkdir_p(params[:build_path])
        relative_path = Pathname.new(".").relative_path_from(Pathname.new(params[:build_path])).to_s

        UI.message "Relative pro path: #{relative_path}/Vremenar.pro"

        Dir.chdir(params[:build_path]) do
          Actions.sh "qmake #{relative_path}/Vremenar.pro -spec macx-ios-clang CONFIG+=release CONFIG+=iphoneos CONFIG+=device CONFIG+=qtquickcompiler CONFIG+=store"
        end

        Actions.lane_context[SharedValues::RUN_QMAKE_PROJECT_PATH] = "#{params[:build_path]}/Vremenar.xcodeproj"
      end

      #####################################################
      # @!group Documentation
      #####################################################

      def self.description
        "Run qmake to prepare the Xcode project"
      end

      def self.details
        "This action runs qmake with configured settings. Used to prepare the Xcode project for the standard build_app action."
      end

      def self.available_options
        [
          FastlaneCore::ConfigItem.new(key: :build_path,
                                       env_name: "FL_RUN_QMAKE_BUILD_PATH",
                                       description: "Build path",
                                       is_string: true,
                                       default_value: "fastlane/build/ios/qmake")
        ]
      end

      def self.output
        [
          ['RUN_QMAKE_PROJECT_PATH', 'Created project path']
        ]
      end

      def self.authors
        ["@ntadej"]
      end

      def self.is_supported?(platform)
        platform == :ios
      end
    end
  end
end
