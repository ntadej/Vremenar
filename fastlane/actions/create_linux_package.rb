# frozen_string_literal: true

module Fastlane
  module Actions
    module SharedValues
      CREATE_LINUX_PACKAGE_OUTPUT_FILE = :CREATE_LINUX_PACKAGE_OUTPUT_FILE
    end

    class CreateLinuxPackageAction < Action
      def self.run(params)
        build_path = params[:path] || Actions.lane_context[SharedValues::RUN_CMAKE_PROJECT_PATH]
        output_path = Actions.lane_context[SharedValues::RUN_CMAKE_OUTPUT_PATH] || build_path
        relative_source_path = Pathname.new('.').relative_path_from(Pathname.new(build_path) / 'install')
        relative_output_path = Pathname.new(output_path).relative_path_from(Pathname.new(build_path) / 'install')

        UI.message "Build path: #{build_path}"
        UI.message "Output path: #{output_path}"

        deploy_tool_url = 'https://github.com/probonopd/linuxdeployqt/releases/download/continuous/linuxdeployqt-continuous-x86_64.AppImage'
        deploy_tool = 'linuxdeployqt-continuous-x86_64.AppImage'

        deploy_tool_path = Pathname.new(output_path) + deploy_tool
        unless deploy_tool_path.exist?
          Actions.sh "curl -L -o #{deploy_tool_path} #{deploy_tool_url}"
          Actions.sh "chmod +x #{deploy_tool_path}"
        end

        output_file_name = 'Vremenar.appimage'

        Dir.chdir build_path do
          Actions.sh 'DESTDIR=install/Vremenar ninja install'

          Dir.chdir 'install' do
            command = '../../linuxdeployqt-continuous-x86_64.AppImage'
            command += ' Vremenar/usr/share/applications/vremenar.desktop'
            command += ' -appimage'
            command += " -qmldir=#{relative_source_path}/src/qml/"
            Actions.sh command

            Actions.sh 'tar -cjf Vremenar.tar.bz2 Vremenar'

            output_files = Pathname.glob '*.AppImage'
            output_files[0].rename 'Vremenar.AppImage'

            FileUtils.mv 'Vremenar.AppImage', relative_output_path
            FileUtils.mv 'Vremenar.tar.bz2', relative_output_path
          end
        end

        output_file = "#{output_path}/#{output_file_name}"
        UI.message "Output file: #{output_file}"

        Actions.lane_context[SharedValues::CREATE_LINUX_PACKAGE_OUTPUT_FILE] = output_file
      end

      #####################################################
      # @!group Documentation
      #####################################################

      def self.description
        'Create Linux package.'
      end

      def self.details
        'Create Linux package.'
      end

      def self.available_options
        [
          FastlaneCore::ConfigItem.new(key: :path,
                                       env_name: 'FL_CREATE_LINUX_PACKAGE_PATH',
                                       description: 'Build path',
                                       is_string: true,
                                       optional: true)
        ]
      end

      def self.output
        [
          ['CREATE_LINUX_PACKAGE_OUTPUT_FILE', 'Created output file']
        ]
      end

      def self.authors
        ['@ntadej']
      end

      def self.is_supported?(platform)
        platform == :linux
      end
    end
  end
end
