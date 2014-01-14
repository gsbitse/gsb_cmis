<?php

/**
 * @file
 * Drush commands for GSB CMIS Test
 */

/**
 * Implements hook_drush_command().
 */
function gsb_cmis_drush_command() {
  $items = array();
  $items['gsb-cmis-ct-import'] = array(
    'description' => 'GSB CMIS Content Type Initial Import',
    'arguments' => array(
      'uuid' => 'The document uuid',
      'content-type' => 'The content type',
    ),    
    'examples' => array(
      'drush --user=1 gsbcmis-ctimport <uuid> <content-type>' => 'Import all docs from a specific Alfresco folder, as the admin user.',
    ),    
    'aliases' => array('gsbcmis-ctimport'),
  ); 
  $items['gsb-import-test'] = array(
    'description' => 'GSB Import Test',
    'arguments' => array(
      'uuid' => 'The document uuid',
      'content-type' => 'The content type',
    ),    
    'examples' => array(
      'drush --user=1 gsb-import-test <uuid> <content-type>' => 'Import all docs from a specific Alfresco folder, as the admin user.',
    ),    
    'aliases' => array('gsb-import-test'),
  ); 
  return $items;
}

/**
 * Implement hook_drush_help().
 */
function gsb_cmis_drush_help($command) {
  switch ($command) {
    case 'drush:gsb-cmis-ct-import':
      return dt('Run cmis content type initial import command');
  }
}

/**
 * Runs the gsb cmsi test doit command
 */
function drush_gsb_cmis_gsb_import_test($uuid = '', $content_type = '') {

  // on prod
  // works - drush gsb-import-test --user=1 urn:uuid:6882bdf7-9b66-4324-be8d-05d085fc093c case
  // works - drush gsb-import-test --user=1 urn:uuid:fb200647-8644-4158-be05-f67794b44356 case
  // doesn't work - gsb-cmis/case/urn:uuid:6882bdf7-9b66-4324-be8d-05d085fc093c?token=qpxmjue3mZ
  // doesn't work - gsb-cmis/case/urn:uuid:fb200647-8644-4158-be05-f67794b44356?token=qpxmjue3mZ

  // on qa
  // works - drush gsb-import-test --user=1 urn:uuid:3224db1c-5db0-484a-a7e3-fb6bbc140df7 case
  // doesn't work - gsb-cmis/case/urn:uuid:3224db1c-5db0-484a-a7e3-fb6bbc140df7?token=qpxmjue3mZ


  // gsbcmis-ctimport
  // drush gsbcmis-ctimport --user=1 urn:uuid:3224db1c-5db0-484a-a7e3-fb6bbc140df7 case

  dpm('test 1 begin -------------');

  $object = gsb_cmis_api_getDocumentObject('default', 'urn:uuid:3224db1c-5db0-484a-a7e3-fb6bbc140df7');
  dpm($object);

  dpm('test 1 done --------------------');

}

/**
 * Runs the gsb cmsi test doit command
 */
function drush_gsb_cmis_ct_import($uuid = '', $content_type = '') {

  drush_log(dt('-------------------------------'), 'success');

  if ($uuid == '') {
    drush_log(dt('gsb cmis content type initial import failed - no uuid'), 'error'); 
    return; 
  }

  //dpm('uuid = ' . $uuid);
  drush_log(dt('uuid = '.$uuid), 'success'); 

  // $content_type should be 'case' or 'working_paper'
  if ($content_type != 'case' && $content_type != 'working_paper') {
    drush_log(dt('gsb cmis content type initial import failed - invalid content type'), 'error'); 
    return; 
  }

  //dpm('content type = ' . $content_type);
  drush_log(dt('content type = ' . $content_type), 'success'); 

  gsb_cmis_content_type_initial_import($content_type, $uuid);   
  
  // log to the command line with an OK status
  drush_log(dt('gsb cmis content type initial import command - completed'), 'ok');  
  
}